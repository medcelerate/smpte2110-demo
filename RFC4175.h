#include <bitset>
#include <vector>


class RFC4175{

    public:
        RFC4175(
            uint8_t V, 
            uint8_t P, 
            uint8_t X,
            uint8_t CC,
            uint8_t PT,
            uint32_t SSRC,
            uint32_t TimeStamp
        );

        ~RFC4175();

        std::vector<bool> ConstructPayloadHeader(
            uint16_t Length,
            uint16_t LineNumber,
            uint16_t Offset,
            bool Continuation,
            bool EndofFrame
            );

        std::vector<bool> ConstructPayload(
            const std::vector<uint8_t> &data,
            uint16_t LineNumber, 
            uint16_t Offset, 
            bool Continuation, 
            bool EndofFrame
        );

    private:
        std::bitset<2> _V;
        std::bitset<1> _P;
        std::bitset<1> _X;
        std::bitset<4> _CC;
        std::bitset<7> _PT;
        std::bitset<32> _SSRC;
        std::bitset<32> _TimeStamp;

    private:
        uint16_t _SequenceNumber {0};
        uint16_t _SequenceNumberEx {0};
        uint16_t _LineNumber {0};

        //std::bitset<16> Length;
        //std::bitset<15> LineNumber;
        //std::bitset<15> Offset;
        //std::bitset<1> F;
        //std::bitset<1> C;

        //std::bitset<1> _M;

        /*pgroup - number of bytes for each pixel
        8bit - 4
        10bit - 5
        12 bit - 6
        16 bit - 8 
        */

};

