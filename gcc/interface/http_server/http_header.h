#ifndef _HTTP_HEADER_H
#define _HTTP_HEADER_H

enum HEADER_TYPE
{
    INDETERMINATE_HEADER = 0,
    GENERAL_HEADER,
    REQUEST_HEADER,
    ENTITY_HEADER
};

class cHeader
{
public:
    cHeader()
        :m_HeaderType(INDETERMINATE_HEADER)                 {};
    cHeader(std::string &header)
        :m_Header(header),
        m_HeaderType(INDETERMINATE_HEADER)                  {};
    ~cHeader()                                              {};

private:
    std::string m_Header;
    HEADER_TYPE m_HeaderType;

};


#endif
