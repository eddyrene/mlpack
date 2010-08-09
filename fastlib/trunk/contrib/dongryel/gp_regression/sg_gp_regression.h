/** @file sg_gp_regression.h
 *
 *  @brief An prototype of "Sparse Greedy Gaussian Process regression" by
 *         Smola et al.
 *
 *  @author Dongryeol Lee (dongryel@cc.gatech.edu)
 */

#ifndef ML_GP_REGRESSION_SG_GP_REGRESSION_H
#define ML_GP_REGRESSION_SG_GP_REGRESSION_H

#include "fastlib/fastlib.h"

namespace ml {
namespace gp_regression {
class SparseGreedyGprModel {
  private:

    const Matrix *dataset_;

    const Vector *targets_;

    double frobenius_norm_targets_;

    std::vector<int> subset_;

    std::vector<int> subset_for_error_;

    std::vector< std::vector<double> > kernel_matrix_subset_;

    std::vector< std::vector<double> > squared_kernel_matrix_;

    std::vector< std::vector<double> > kernel_matrix_;

    std::vector< std::vector<double> > inverse_;

    std::vector< std::vector<double> > inverse_for_error_;

    std::vector<double> subset_coefficients_;

  private:
    template<typename CovarianceType>
    void ComputeKernelValues_(
      const CovarianceType &covariance_in,
      int candidate_index,
      std::vector<double> *kernel_values_out) const;

    void GrowMatrix_(std::vector< std::vector<double> > &matrix);

    void FillSquaredKernelMatrix_();

    void FillKernelMatrix_();

  public:
    SparseGreedyGprModel();

    void Init(const Matrix *dataset_in, const Vector *targets_in);

    template<typename CovarianceType>
    void AddOptimalPoint(
      const CovarianceType &covariance_in,
      double noise_level_in,
      const std::vector<int> &candidate_indices,
      bool for_coeffs);
};

class SparseGreedyGpr {
  private:
    const Matrix *dataset_;

    const Vector *targets_;

  private:

    void InitInactiveSet_(std::vector<int> *inactive_set_out) const;

    void ChooseRandomSubset_(
      const std::vector<int> &inactive_set,
      int subset_size,
      std::vector<int> *subset_out) const;

  public:

    SparseGreedyGpr();

    void Init(const Matrix &dataset_in, const Vector &targets_in);

    template<typename CovarianceType>
    void Compute(
      double noise_level_in,
      double precision_in,
      const CovarianceType &covariance_in,
      SparseGreedyGprModel *model_out);
};
};
};

#endif
