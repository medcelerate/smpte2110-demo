#include "RFC4175.h"
#include <vector>
#include <limits>

RFC4175::RFC4175(uint8_t V, 
                uint8_t P, 
                uint8_t X,
                uint8_t CC,
                uint8_t PT,
                uint32_t SSRC,
                uint32_t TimeStamp): 
                _V (V << 6), _P (P << 7),
                _X (X << 7), _CC (CC << 4),
                _PT (PT << 1), _SSRC (SSRC),
                _TimeStamp(TimeStamp)
{
                


};

std::vector<bool> RFC4175::ConstructPayloadHeader(
            uint16_t Length,
            uint16_t LineNumber,
            uint16_t Offset,
            bool Continuation,
            bool EndofFrame
            )
    {
        std::bitset<16> SequenceNumber (_SequenceNumber);
        std::bitset<16> SequenceNumberEx (_SequenceNumberEx);
        std::bitset<16> Length_BT (Length);
        std::bitset<15> LineNumber_BT (LineNumber << 1);
        std::bitset<15> Offset_BT (Offset << 1);


    
    std::vector<bool> h;

    for (int i {0}; i < (int)_V.size(); i++) {
        h.push_back(_V[i]);
    };

    for (int i {0}; i < (int)_P.size(); i++) {
        h.push_back(_P[i]);
    };

    for (int i {0}; i < (int)_X.size(); i++) {
        h.push_back(_X[i]);
    };

    for (int i {0}; i < (int)_CC.size(); i++) {
        h.push_back(_CC[i]);
    };

    //M
    h.push_back(EndofFrame);


    for (int i {0}; i < (int)_PT.size(); i++) {
        h.push_back(_PT[i]);
    };

    for (int i {0}; i < (int)SequenceNumber.size(); i++) {
        h.push_back(SequenceNumber[i]);
    };

    for (int i {0}; i < (int)_TimeStamp.size(); i++) {
        h.push_back(_TimeStamp[i]);
    };

    for (int i {0}; i < (int)_SSRC.size(); i++) {
        h.push_back(_SSRC[i]);
    };

    for (int i {0}; i < (int)SequenceNumberEx.size(); i++) {
        h.push_back(SequenceNumberEx[i]);
    };


    for (int i {0}; i < (int)Length_BT.size(); i++) {
        h.push_back(Length_BT[i]);
    };

    //F
    h.push_back(0);

    for (int i {0}; i < (int)LineNumber_BT.size(); i++) {
        h.push_back(LineNumber_BT[i]);
    };

    h.push_back(Continuation);

    for (int i {0}; i < (int)Offset_BT.size(); i++) {
        h.push_back(Offset_BT[i]);
    };

    if (_SequenceNumber == std::numeric_limits<uint16_t>::max()) {
        _SequenceNumber++;
    } else {
        _SequenceNumberEx++;
    }

    return h;

};

std::vector<bool> RFC4175::ConstructPayload(
    const std::vector<uint8_t> &data, 
    uint16_t LineNumber, 
    uint16_t Offset, 
    bool Continuation, 
    bool EndofFrame) {

    std::vector<bool> Header = ConstructPayloadHeader(
        (uint8_t)data.size(),
        LineNumber,
        Offset,
        Continuation,
        EndofFrame
    );

    std::vector<bool> DataFrame = Header;

    for (const uint8_t& a: data) {
        std::bitset<8> x (a);
        for (int i {0}; i < (int)x.size(); i++) {
            DataFrame.push_back(x[i]);
        };
    }


    return DataFrame;

}

//Offset is how many pixels you are into the scan line.
//LineNumber is the current scan line


