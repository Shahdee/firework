#ifndef __PerformanceTest_h__
#define __PerformanceTest_h__

#if defined(_MSC_VER) && (_MSC_VER > 1300)
#pragma once
#endif

namespace Render {
	class Target;
	class Texture;
}

///
/// »змер€ет производительность видеосистемы
///
class PerformanceTest {
public:
	static const int kTargetSize = 512;
	static const int kTextureSize = 256;
	static const int kLoopSize = 20000;
	static const int kEstimateCount = 5;
	
	PerformanceTest();
	~PerformanceTest();
	
	float Estimate(int loopSize = kLoopSize, int estimateCount = kEstimateCount) const;

private:
	float Run(int loopSize) const;
	
	PerformanceTest(const PerformanceTest&);
	const PerformanceTest& operator=(const PerformanceTest&);

private:
	Render::Target* _target;
	Render::Texture* _texture;
};

#endif // __PerformanceTest_h__
