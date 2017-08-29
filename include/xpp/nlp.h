/**
 @file    nlp.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Jul 1, 2016
 @brief   Brief description
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_OPT_NLP_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_OPT_NLP_H_

#include <memory>
#include <vector>
#include <Eigen/Dense>

#include "bound.h"
#include <xpp/composite.h>

namespace xpp {
namespace opt {

enum NlpSolver { Ipopt, Snopt };

/** @brief Nonlinear Programming problem definition
  *
  * This class is responsible for holding all the information of a
  * Nonlinear Program, which includes the optimization variables, their bounds,
  * the cost function, the constraint function, constraint bounds and possibly
  * derivatives.
  */
class NLP {
public:
  using Number                   = double;
  using OptimizationVariablesPtr = std::shared_ptr<Composite>;
  using ConstraintPtrU           = std::unique_ptr<Component>;

  NLP ();
  virtual ~NLP ();

  void Init(const OptimizationVariablesPtr&);
  void SetVariables(const Number* x);

  int GetNumberOfOptimizationVariables() const;
  bool HasCostTerms() const;
  VecBound GetBoundsOnOptimizationVariables() const;
  VectorXd GetStartingValues() const;

  double EvaluateCostFunction(const Number* x);
  VectorXd EvaluateCostFunctionGradient(const Number* x);

  int GetNumberOfConstraints() const;
  VecBound GetBoundsOnConstraints() const;
  VectorXd EvaluateConstraints(const Number* x);

  void EvalNonzerosOfJacobian(const Number* x, Number* values);
  Jacobian GetJacobianOfConstraints() const;

  void AddCost(ConstraintPtrU);
  void AddConstraint(ConstraintPtrU);

  void PrintCurrent() const;

  /** @brief saves the current values of the optimization variables.
   *
   *  This is used to keep a history of the values for each NLP iterations.
   */
  void SaveCurrent();

  OptimizationVariablesPtr GetOptVariables(int iter);
  int GetIterationCount() const { return x_prev.size(); };

private:
  ConstraintPtrU constraints_;
  ConstraintPtrU costs_;
  OptimizationVariablesPtr opt_variables_;

  std::vector<VectorXd> x_prev;

  VectorXd ConvertToEigen(const Number* x) const;
};

} /* namespace opt */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_OPT_NLP_H_ */