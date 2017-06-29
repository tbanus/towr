/**
 @file    linear_constraint.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    May 26, 2016
 @brief   Implements a special form of constraint, namely linear.
 */

#ifndef XPP_OPT_INCLUDE_XPP_OPT_LINEAR_CONSTRAINT_H_
#define XPP_OPT_INCLUDE_XPP_OPT_LINEAR_CONSTRAINT_H_

#include <memory>
#include <string>

#include <xpp/bound.h>
#include <xpp/matrix_vector.h>

#include "composite.h"

namespace xpp {
namespace opt {

/** @brief Calculates the constraint violations for linear constraints.
  *
  * This class is responsible for getting the current state of the CoM spline
  * and using this to calculate the constraint violations.
  */
class LinearEqualityConstraint : public Primitive {
public:

  /** @brief Defines the elements of the linear constraint as g = Mx+v.
    *
    * @param opt_vars_       This is where the vector x is taken from.
    * @param linear_equation The matrix M and vector v.
    * @param variable_name   The name of the variables x.
    */
  LinearEqualityConstraint (const OptVarsPtr& opt_vars_,
                            const MatVec& linear_equation,
                            const std::string& variable_name);
  virtual ~LinearEqualityConstraint ();

  /** @brief Returns a vector of constraint violations for current variables \c x_coeff. */
  VectorXd GetValues() const override;
  VecBound GetBounds() const override;
  void FillJacobianWithRespectTo (std::string var_set, Jacobian&) const override;

private:
  MatVec linear_equation_;
  std::string variable_name_;
};

} /* namespace opt */
} /* namespace xpp */

#endif /* XPP_OPT_INCLUDE_XPP_OPT_LINEAR_CONSTRAINT_H_ */
