#include "pankov_a_string_word_count/seq/include/ops_seq.hpp"

#include <numeric>
#include <vector>

#include "pankov_a_string_word_count/common/include/common.hpp"
#include "util/include/util.hpp"

namespace pankov_a_string_word_count {

PankovAStringWordCountSEQ::PankovAStringWordCountSEQ(const InType &in) {
  SetTypeOfTask(GetStaticTypeOfTask());
  GetInput() = in;
  GetOutput() = 0;
}

bool PankovAStringWordCountSEQ::ValidationImpl() {
  return GetOutput() == 0;
}

bool PankovAStringWordCountSEQ::PreProcessingImpl() {
  GetOutput() = 0;
  return true;
}

static OutType CountWordsInString(const std::string& s) {
  int count = 0;
  bool in_word = false;

  for (unsigned char uc : s) {
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

bool PankovAStringWordCountSEQ::RunImpl() {
  const std::string& s = GetInput();
  GetOutput() = CountWordsInString(s);
  return true;
}


bool PankovAStringWordCountSEQ::PostProcessingImpl() {
  return GetOutput() >= 0;
}

}  // namespace pankov_a_string_word_count
