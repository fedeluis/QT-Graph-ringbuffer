#ifndef RBUF_RINGBUFFER_CPP
#define RBUF_RINGBUFFER_CPP

#include "RingBuffer.hpp"

namespace rbuf {

    RingBuffer::RingBuffer(unsigned int num_samples, unsigned int num_channels) {
        if(num_samples<=0 || num_channels<=0) {
            do {
                printf("Invalid input for data structure parameters!\n");
                printf("Insert a new valid number of samples [1,N]: ");
                scanf("%u", &num_samples);
                printf("\nInsert a new valid number of channels [1,N]: ");
                scanf("%u", &num_channels);
            } while(num_samples<=0 || num_channels<=0);
        }
        this->_buffer=Eigen::MatrixXd(num_samples, num_channels);

        this->nsamples=num_samples;
        this->nchannels=num_channels;

        this->add_index=0;
        this->get_index=0;

        this->read_mtx.lock();
        this->allow_read=false;

        this->write_mtx.lock();
        this->allow_write=true;
    }

    RingBuffer::~RingBuffer() {
    }

    unsigned int RingBuffer::getSamples() {
        return this->nsamples;
    }

    unsigned int RingBuffer::getChannels() {
        return this->nchannels;
    }

    void RingBuffer::add(const Eigen::Ref<const Eigen::MatrixXd>& in) {
        unsigned int inChannels=in.cols();
        unsigned int bufChannels=this->getChannels();

        if(inChannels!=bufChannels) {
            throw std::invalid_argument("Input invalid in function add()\nThe lenght of the channels is not the same!");
        }

        unsigned int inSamples=in.rows();
        unsigned int bufSamples=this->getSamples();
        /**
         * Colonna per colonna inserisco i dati in _buffer, controllando di non
         * inserirne dove non è stato ancora letto nulla
         */
        for(unsigned int i=0; i<inSamples; i++) {
            // se esaurisco lo spazio in scrittura nel buffer e sono autorizzato a scrivere
            if( (this->add_index==this->get_index-1) && (this->allow_write==true) ) {
                this->allow_write=false;
                this->write_mtx.lock();  // in attesa fino a sblocco in RingBuffer::get()
            }
            this->_buffer.block(0,this->add_index,bufChannels,1)=in.block(0,i,inChannels,1);
            /**
             * aggiornamento contatore ad anello per inserimento
             * 
             * non utilizzo % per non avere problemi di dimensionamento dopo molti cicli
             */
            if(this->add_index+1==bufSamples)
                this->add_index=0;
            else
                this->add_index++;
            
            /**
             * Dopo aver scritto almeno una colonna permetto la lettura
             * Sblocco di read_mtx in RingBuffer::get()
             */
            if(this->allow_read==false) {
                this->allow_read=true;
                this->read_mtx.unlock();
            }
        }
    }

    void RingBuffer::get(Eigen::Ref<Eigen::MatrixXd> out) {
        unsigned int outChannels=out.cols();
        unsigned int bufChannels=this->getChannels();

        if(outChannels!=bufChannels) {
            throw std::invalid_argument("Input invalid in function get()\nThe lenght of the channels is not the same!");
        }

        // formulazione generale, out dovrebbe essere vettore
        unsigned int outSamples=out.rows();
        unsigned int bufSamples=this->getSamples();
        
        //Aspetto inserimento primo valore per poter cominciare a leggere
        if( (this->add_index==0) && (this->get_index==0) )
            this->read_mtx.lock();
            
        /**
         * Colonna per colonna inserisco i dati in out, controllando di non
         * leggere dove non è stato ancora stato inserito od aggiornato nulla
         */
        for(unsigned int i=0; i<outSamples; i++) {
            // se esaurisco lo spazio in lettura nel buffer e sono autorizzato a leggere
            if( (this->get_index+1==this->add_index) && (this->allow_read==true) ) {
                this->allow_read=false;
                this->read_mtx.lock();  // in attesa fino a sblocco in RingBuffer::add()
            }
            out.block(0,i,outChannels,1)=this->_buffer.block(0,this->get_index,bufChannels,1);

            if(this->get_index+1==bufSamples)
                this->get_index=0;
            else
                this->get_index++;

            /**
             * Dopo aver letto almeno una colonna permetto la scrittura
             * Sblocco di write_mtx in RingBuffer::add()
             */
            if(this->allow_write==false) {
                this->allow_write=true;
                this->write_mtx.unlock();
            }
        }
    }
}

#endif