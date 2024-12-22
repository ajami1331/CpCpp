#ifndef TeeBuf_h
#define TeeBuf_h 1

#include <streambuf>

class TeeBuf : public std::streambuf {
public:
    TeeBuf(std::streambuf* sb1, std::streambuf* sb2)
        : sb1_(sb1), sb2_(sb2) {}

protected:
    // Override the overflow method to write to both buffers
    virtual int overflow(int c) override {
        if (c == EOF) {
            return !EOF;
        } else {
            int const r1 = sb1_->sputc(c);
            int const r2 = sb2_->sputc(c);
            return (r1 == EOF || r2 == EOF) ? EOF : c;
        }
    }

    // Override the sync method to synchronize both buffers
    virtual int sync() override {
        int const r1 = sb1_->pubsync();
        int const r2 = sb2_->pubsync();
        return (r1 == 0 && r2 == 0) ? 0 : -1;
    }

private:
    std::streambuf* sb1_;
    std::streambuf* sb2_;
};

#endif // TeeBuf_h