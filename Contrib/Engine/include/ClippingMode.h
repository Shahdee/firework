#ifndef _CLIPPINGMODE_H_
#define _CLIPPINGMODE_H_

//
// Класс обрезания
//
class ClippingMode {
	friend bool operator == (const ClippingMode& first, const ClippingMode& second);
	friend bool operator != (const ClippingMode& first, const ClippingMode& second);
private:

	bool _isLeft;
	bool _isTop;
	bool _isRight;
	bool _isBottom;

	ClippingMode(bool isLeft, bool isTop, bool isRight, bool isBottom);

public:

	static const ClippingMode NONE;
	static const ClippingMode LEFT;
	static const ClippingMode TOP;
	static const ClippingMode RIGHT;
	static const ClippingMode BOTTOM;
	static const ClippingMode LEFT_RIGHT;
	static const ClippingMode TOP_BOTTOM;
	static const ClippingMode ALL;

	bool IsLeft();

	bool IsTop();

	bool IsRight();

	bool IsBottom();

	static ClippingMode Add(ClippingMode first, ClippingMode second);

	static ClippingMode Sub(ClippingMode first, ClippingMode second);
};

inline ClippingMode operator + (ClippingMode first, ClippingMode second) {
	return ClippingMode::Add(first, second);
}

inline ClippingMode operator - (ClippingMode first, ClippingMode second) {
	return ClippingMode::Sub(first, second);
}

bool operator == (const ClippingMode& first, const ClippingMode& second);
bool operator != (const ClippingMode& first, const ClippingMode& second);

#endif
