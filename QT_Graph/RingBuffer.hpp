#ifndef RBUF_RINGBUFFER_HPP
#define RBUF_RINGBUFFER_HPP

#include <eigen3/Eigen/Dense>
#include <thread>   // std::thread
#include <mutex>    // std::mutex
#include <stdexcept>

namespace rbuf {
    /*! \brief This class implements a ring circular buffer
     */
    class RingBuffer {

        public:
            /*! \brief  Costructor
             *  \param  num_samples    Number of samples in the buffer
             *  \param  num_channels   Number of channels in the buffer
             */
            RingBuffer(unsigned int num_samples, unsigned int num_channels);
            
            /*! \brief  Destructor
             */
            ~RingBuffer();

            /*! \brief  Get the number of samples in the buffer
             *  \return Number of samples
             */
            unsigned int getSamples();

            /*! \brief  Get the number of channels in the buffer
             *  \return Number of channels
             */
            unsigned int getChannels();

            /*! \brief  Add data frame to the buffer
             *  \param  in  Frame of data in the format of [samples x channels]
             *  \throws std::invalid_argument
             */
            void add(const Eigen::Ref<const Eigen::MatrixXd>& in);

            /*! \brief  Method to return data to the buffer
             *  \param  out Reference to the data stored in the buffer
             *  \throws std::invalid_argument
             */
            void get(Eigen::Ref<Eigen::MatrixXd> out);

        private:
            /*! \brief  Ringbuffer data
             */
            Eigen::MatrixXd _buffer;
            unsigned int nsamples;
            unsigned int nchannels;
            /*! \brief  Index where to insert the data
             */
            unsigned int add_index;
            /*! \brief  Index where to read the data
             */
            unsigned int get_index;
            /*! \brief  Mutex against read error
             */
            std::mutex read_mtx;
            bool allow_read;
            /*! \brief  Mutex against write error
             */
            std::mutex write_mtx;
            bool allow_write;

        public:
            /*! \brief Eigen flag to keep the memory block of the matrix aligned
		     */
		    EIGEN_MAKE_ALIGNED_OPERATOR_NEW        
    };
}

#endif