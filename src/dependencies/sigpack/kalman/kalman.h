// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef KALMAN_H
#define KALMAN_H
namespace sp
{
    ///
    /// @defgroup filter Filter
    /// \brief Kalman predictor/filter functions.
    /// @{

    ///
    /// \brief Kalman filter class.
    ///
    /// Implements Kalman functions for the system
    /// \f[ x_k = Ax_{k-1}+Bu_{k-1} + w_{k-1}  \f]
    /// with measurements
    /// \f[ z_k = Hx_k + v_k  \f]
    /// The predicting stage is
    /// \f[ \hat{x}^-_k = \hat{x}_{k-1}+Bu_{k-1} \f]
    /// \f[ P^-_k = AP_{k-1}A^T+Q \f]
    /// and the updates stage
    /// \f[ K_k = P^-_kH^T(HP^-_kH^T+R)^{-1} \f]
    /// \f[ \hat{x}_k = \hat{x}^-_k + K_k(z_k-H\hat{x}^-_k) \f]
    /// \f[ P_k = (I-K_kH)P^-_k \f]
    ///
    /// For detailed info see: http://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf

    class KF
    {
    private:
        arma::uword N;       ///< Number of states
        arma::uword M;       ///< Number of inputs
        arma::uword L;       ///< Number of measurements/observations

        arma::mat x;         ///< State vector
        arma::mat z_e;       ///< Prediction error


        arma::mat A;         ///< State transition matrix
        arma::mat B;         ///< Input matrix
        arma::mat H;         ///< Measurement matrix

        arma::mat P;         ///< Error covariance matrix (estimated accuracy)
        arma::mat Q;         ///< Process noise  = E[W x Wt]
        arma::mat R;         ///< Measurement noise
        arma::mat K;         ///< Kalman gain vector
    public:
        ////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ////////////////////////////////////////////////////////////////////////////////////////////
        KF(arma::uword _N,arma::uword _M,arma::uword _L)
        {
            N = _N;   // Nr of states
            M = _M;   // Nr of measurements/observations
            L = _L;   // Nr of inputs
            x.set_size(N,1);x.zeros();
            z_e.set_size(M,1);z_e.zeros();
            A.set_size(N,N);A.eye();
            B.set_size(N,L);B.zeros();
            H.set_size(M,N);H.zeros();
            P.set_size(N,N);P.eye();
            Q.set_size(N,N);Q.eye();
            R.set_size(M,M);R.eye();
            K.set_size(N,M);K.zeros();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ////////////////////////////////////////////////////////////////////////////////////////////
        ~KF(){}

        ////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Clear the internal states and pointer.
        ////////////////////////////////////////////////////////////////////////////////////////////
        void clear(void)
        {
            K.zeros();
            P.eye();
            x.zeros();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        void set_x(const arma::mat &_x)  { x = _x; } // Set state vector.[Nx1]
        void set_A(const arma::mat &_A)  { A = _A; } // Set state transition matrix.[NxN]
        void set_B(const arma::mat &_B)  { B = _B; } // Set input matrix.[NxL]
        void set_H(const arma::mat &_H)  { H = _H; } // Set measurement matrix.[MxN]
        void set_P(const arma::mat &_P)  { P = _P; } // Set error covariance matrix.[NxN]
        void set_Q(const arma::mat &_Q)  { Q = _Q; } // Set process/state noise cov. matrix.[NxN]
        void set_R(const arma::mat &_R)  { R = _R; } // Set measurement noise cov. matrix.[MxM]
        void set_K(const arma::mat &_K)  { K = _K; } // Set Kalman gain matrix.[NxM]

        arma::mat get_x(void)   { return x; }   // Get states [Nx1]
        arma::mat get_err(void) { return z_e; } // Get pred error [Mx1]
        arma::mat get_K(void)   { return K; }   // Get Kalman gain [NxM]
        arma::mat get_P(void)   { return P; }   // Get error cov matrix [NxN]

        ////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Predict the internal states.
        ////////////////////////////////////////////////////////////////////////////////////////////
        void predict(void)
        {
           // Project the state ahead
           x = A*x;

           // Project the error covariance ahead
           P = A*P*A.t()+Q;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Predict the internal states using a control input.
        /// @param u Input/control signal
        ////////////////////////////////////////////////////////////////////////////////////////////
        void predict(const arma::mat u )
        {
           // Project the state ahead
           x = A*x+B*u;

           // Project the error covariance ahead
           P = A*P*A.t()+Q;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Correct and update the internal states.
        ////////////////////////////////////////////////////////////////////////////////////////////
        void update(const arma::mat z )
        {
           // Compute the Kalman gain
           K = P*H.t()*pinv(H*P*H.t()+R);

           // Update estimate with measurement z
           x = x+K*(z-H*x);
           z_e = z-H*x;

           // Joseph’s form covariance update
           arma::mat Jf = arma::eye<arma::mat>(N,N)-K*H;
           P = Jf*P*Jf.t() + K*R*K.t();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Rauch-Tung-Striebel smoother.
        ////////////////////////////////////////////////////////////////////////////////////////////
        void rts_smooth(const arma::mat& Xf, const arma::cube& Pf, arma::mat& Xs, arma::cube& Ps )
        {
           arma::uword Nf = Xf.n_cols;
           arma::mat P_pred(N,N);
           arma::mat C(N,N);
           arma::mat Q_hat(N,N);

           // Copy forward data
           Xs = Xf;
           Ps = Pf;

           // Backward filter
           for(arma::uword n=Nf-2;n>0;n--)
           {
               // Project the error covariance
               P_pred = A*Pf.slice(n)*A.t()+Q;

               // Update
               C = Pf.slice(n)*A.t()*pinv(P_pred);
               Xs.col(n) += C*(Xs.col(n+1)-A*Xs.col(n));
               Ps.slice(n) += C*(Ps.slice(n+1)-P_pred)*C.t();

           }

        }

    }; // End class KF
}
#endif // KALMAN_H
