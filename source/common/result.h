#ifndef RESULT_H
#define RESULT_H

const unsigned int TYPE_RESULT_NONE = 0x0;

class Result
{
public:
	/* Type information for dynamic cast
	 * I do not know another way for applying results */
	const unsigned int type;
	Result(unsigned int t = TYPE_RESULT_NONE)
		: type(t)
	{

	}
	virtual ~Result()
	{

	}
};

#endif // RESULT_H
