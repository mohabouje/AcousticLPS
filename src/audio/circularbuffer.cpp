#include "circularbuffer.h"


CircularBuffer::CircularBuffer(uint size) :
    _buffer(boost::circular_buffer<Real>(size))
{

}

void CircularBuffer::append(const Real *tmp, uint size)
{
    for (uint i=0; i<size; i++) {
        _buffer.push_back(tmp[i]);
    }
}
