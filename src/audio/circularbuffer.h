#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include <config.h>
#include <boost/circular_buffer.hpp>
class CircularBuffer
{
public:
    CircularBuffer(uint size);
    void append(const Real* tmp, uint size);
    const boost::circular_buffer<Real>& buffer() const { return _buffer; }
    const Real* data() {  return _buffer.linearize(); }
private:
    boost::circular_buffer<Real> _buffer;
};

#endif // CIRCULARBUFFER_H
