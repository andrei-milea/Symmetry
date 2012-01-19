#ifndef FACTORIAL_H_
#define FACTORIAL_H_


//compute factorial at compile time
//used for group size
//maximum size -- 17
//TODO increase the alowed size [array of const]


template <std::size_t VAL>
struct Factorial
{
	enum { value = VAL * Factorial<VAL - 1>::value };
};

template <>
struct Factorial<0>
{
	enum { value = 1 };
};


#endif


