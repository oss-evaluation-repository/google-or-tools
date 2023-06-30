// Copyright 2010-2022 Google LLC
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// A pybind11 wrapper for knapsack_solver.

#include <string>

#include "ortools/algorithms/knapsack_solver.h"
#include "pybind11/pybind11.h"
#include "pybind11/pytypes.h"
#include "pybind11/stl.h"

using ::operations_research::KnapsackSolver;

namespace py = pybind11;
using ::py::arg;

PYBIND11_MODULE(pywrapknapsack_solver, m) {
  py::class_<KnapsackSolver>(m, "KnapsackSolver")
      .def(py::init<KnapsackSolver::SolverType, const std::string&>())
      .def("Init", &KnapsackSolver::Init, arg("profits"), arg("weights"),
           arg("capacities"))
      .def("Solve", &KnapsackSolver::Solve)
      .def("BestSolutionContains", &KnapsackSolver::BestSolutionContains,
           arg("item_id"))
      .def("IsSolutionOptimal", &KnapsackSolver::IsSolutionOptimal)
      .def("set_time_limit", &KnapsackSolver::set_time_limit,
           arg("time_limit_seconds"))
      .def("set_use_reduction", &KnapsackSolver::set_use_reduction,
           arg("use_reduction"));

  py::enum_<KnapsackSolver::SolverType>(m, "SolverType")
      .value("KNAPSACK_MULTIDIMENSION_BRANCH_AND_BOUND_SOLVER",
             KnapsackSolver::SolverType::
                 KNAPSACK_MULTIDIMENSION_BRANCH_AND_BOUND_SOLVER)
      .value("KNAPSACK_BRUTE_FORCE_SOLVER",
             KnapsackSolver::SolverType::KNAPSACK_BRUTE_FORCE_SOLVER)
      .value("KNAPSACK_64ITEMS_SOLVER",
             KnapsackSolver::SolverType::KNAPSACK_64ITEMS_SOLVER)
      .value("KNAPSACK_DYNAMIC_PROGRAMMING_SOLVER",
             KnapsackSolver::SolverType::KNAPSACK_DYNAMIC_PROGRAMMING_SOLVER)
#if defined(USE_CBC)
      .value("KNAPSACK_MULTIDIMENSION_CBC_MIP_SOLVER",
             KnapsackSolver::SolverType::KNAPSACK_MULTIDIMENSION_CBC_MIP_SOLVER)
#endif  // USE_CBC
#if defined(USE_SCIP)
      .value(
          "KNAPSACK_MULTIDIMENSION_SCIP_MIP_SOLVER",
          KnapsackSolver::SolverType::KNAPSACK_MULTIDIMENSION_SCIP_MIP_SOLVER)
#endif  // USE_SCIP
      .value("KNAPSACK_DIVIDE_AND_CONQUER_SOLVER",
             KnapsackSolver::SolverType::KNAPSACK_DIVIDE_AND_CONQUER_SOLVER)
      .export_values();
}
