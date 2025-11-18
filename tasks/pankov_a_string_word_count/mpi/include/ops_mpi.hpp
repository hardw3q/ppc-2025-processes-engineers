#pragma once

#include "example_processes/common/include/common.hpp"
#include "task/include/task.hpp"

namespace pankov_a_string_word_count {

class PankovAStringWordCount : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kMPI;
  }
  explicit PankovAStringWordCount(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;
};

}  // namespace nesterov_a_test_task_processes
