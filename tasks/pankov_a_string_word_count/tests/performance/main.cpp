#include <gtest/gtest.h>

#include <string>

#include "pankov_a_string_word_count/common/include/common.hpp"
#include "pankov_a_string_word_count/mpi/include/ops_mpi.hpp"
#include "pankov_a_string_word_count/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"
#include "util/include/util.hpp"

namespace pankov_a_string_word_count {

class PankovARunPerfTestProcesses
    : public ppc::util::BaseRunPerfTests<InType, OutType> {
  InType  input_data_{};
  OutType expected_output_{};

  void SetUp() override {
    input_data_ =
        "one two three four five six seven eight nine ten";
    expected_output_ = 10;
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return output_data == expected_output_;
  }

  InType GetTestInputData() final {
    return input_data_;
  }
};

TEST_P(PankovARunPerfTestProcesses, RunPerfModes) {
  ExecuteTest(GetParam());
}

const auto kAllPerfTasks =
    ppc::util::MakeAllPerfTasks<InType,
                                PankovAStringWordCountMPI,
                                PankovAStringWordCountSEQ>(
        PPC_SETTINGS_example_processes);

const auto kGtestValues  = ppc::util::TupleToGTestValues(kAllPerfTasks);
const auto kPerfTestName =
    PankovARunPerfTestProcesses::CustomPerfTestName;

INSTANTIATE_TEST_SUITE_P(RunModeTests,
                         PankovARunPerfTestProcesses,
                         kGtestValues,
                         kPerfTestName);

}  // namespace pankov_a_string_word_count
