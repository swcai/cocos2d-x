#ifndef __SCROLL_H__
#define __SCROLL_H__

#include "cocos2d.h"

class ScrollingSprite : public cocos2d::CCSprite {
protected:
	bool _autoFilled;
	double _velocityX;
	double _velocityY;
}

#endif /* __SCROLL_H__ */
