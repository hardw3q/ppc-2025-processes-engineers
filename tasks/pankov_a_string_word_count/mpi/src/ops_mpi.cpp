#include "pankov_a_string_word_count/mpi/include/ops_mpi.hpp"

#include <mpi.h>

#include <numeric>
#include <vector>

#include "pankov_a_string_word_count/common/include/common.hpp"
#include "util/include/util.hpp"

namespace pankov_a_string_word_count {

PankovAStringWordCountMPI::PankovAStringWordCountMPI(const InType &in) {
  SetTypeOfTask(GetStaticTypeOfTask());
  GetInput() = in;
  GetOutput() = 0;
}

bool PankovAStringWordCountMPI::ValidationImpl() {
  return GetOutput() == 0;
}

bool PankovAStringWordCountMPI::PreProcessingImpl() {
  GetOutput() = 0;
  return true;
}

static int CountWordsLocal(const std::string& s, std::size_t start, std::size_t end) {
  int count = 0;
  bool in_word = false;

  for (std::size_t i = start; i < end; ++i) {
    unsigned char uc = static_cast<unsigned char>(s[i]);
    if (!std::isspace(uc)) {
      if (!in_word) {
        in_word = true;
        ++count;
      }
    } else {
      in_word = false;
    }
  }

  return count;
}

bool PankovAStringWordCountMPI::RunImpl() {
  const std::string& s = GetInput();
  const std::size_t n = s.size();

  int rank = 0;
  int size = 1;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (n == 0) {
    GetOutput() = 0;
    MPI_Barrier(MPI_COMM_WORLD);
    return true;
  }

  std::size_t base = n / static_cast<std::size_t>(size);
  std::size_t rem  = n % static_cast<std::size_t>(size);

  std::size_t start = rank * base + static_cast<std::size_t>(std::min(rank, static_cast<int>(rem)));
  std::size_t end   = start + base + (rank < static_cast<int>(rem) ? 1 : 0);

  if (start > n) start = n;
  if (end > n) end = n;

  if (rank != 0 && start < n) {
    if (!std::isspace(static_cast<unsigned char>(s[start])) &&
        !std::isspace(static_cast<unsigned char>(s[start - 1]))) {
      while (start < end &&
             !std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
      }
    }
  }

  if (start > end) start = end;

  int local_count = 0;
  if (start < end) {
    local_count = CountWordsLocal(s, start, end);
  }

  int global_count = 0;

  MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  MPI_Bcast(&global_count, 1, MPI_INT, 0, MPI_COMM_WORLD);

  GetOutput() = global_count;

  MPI_Barrier(MPI_COMM_WORLD);
  return true;
}

bool PankovAStringWordCountMPI::PostProcessingImpl() {
  return GetOutput() >= 0;
}

}  // namespace pankov_a_string_word_count
