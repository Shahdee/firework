#ifndef __KEYFRAMEDANIMATIONCHANNEL_H__
#define __KEYFRAMEDANIMATIONCHANNEL_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/AnimationChannel.h"
#include "Utils/Quaternion.h"

namespace SceneGraph {

class KeyFramedAnimation;

typedef boost::weak_ptr<KeyFramedAnimation> KeyFramedAnimationWeakPtr;

typedef boost::shared_ptr<KeyFramedAnimation> KeyFramedAnimationHardPtr;
	// Здесь определяется дублирующий тип ссылки для класса KeyFramedAnimation,
	// т.к. мы не можем включить здесь весь заголовочный файл во имя предотвращения
	// циклической зависимости.

///
/// Канал анимации, основанной на ключевых кадрах.
///
class KeyFramedAnimationChannel : public AnimationChannel {
public:
	typedef boost::shared_ptr<KeyFramedAnimationChannel> HardPtr;
	
	typedef boost::weak_ptr<KeyFramedAnimationChannel> WeakPtr;
	
	///
	/// Перечисляет поведение канала анимации.
	///
	enum Behaviour {
		Default = 0,
			/// Значение трансформации узла по-умолчанию
		Constant = 1,
			/// Ближайшее значение ключа без интерполяции
		Linear = 2,
			/// Линейно интерполированное значение двух соседних ключей
		Spline = 3,
			/// Интерполированное сплайном значение двух соседних ключей
		Repeat = 8
			/// Повторяющаяся анимация. Значение n < k < m следует расчитывать как (t-n) % (|m-n|).
	};
	
	KeyFramedAnimationChannel(const std::string& name, KeyFramedAnimationWeakPtr animation);
	
	// KeyFramedAnimationChannel(const KeyFramedAnimationChannel& rhs);
	// KeyFramedAnimationChannel& operator = (const KeyFramedAnimationChannel&);
		//
		// Конструктор копий и оператор присваивания подходят те,
		// что автоматически создаст компилятор.
		// Новая копия ключей анимации не нужна и даже немного вредна,
		// поэтому они сохраняются в указателях.
	
	AnimationChannel::HardPtr Clone();
	
	KeyFramedAnimationHardPtr GetAnimation() const;
		/// Возвращает объект анимации, которой принадлежит канал
	
	void SetAnimation(KeyFramedAnimationHardPtr animation);
		/// Устанавливает объект анимации, которой должен приналдежать канал
	
	void AddPositionKey(double time, const math::Vector3& position);
		/// Добавляет ключ позиции
	
	void AddRotationKey(double time, const math::Quaternion& rotation);
		/// Добавляет ключ поворота
	
	void AddScalingKey(double time, const math::Vector3& scale);
		/// Добавляет ключ масштабирования
	
	void AddTransformKey(double time, const math::Matrix4& transform);
		/// Добавляет ключ трансформации
	
	void SortKeyFrames();
		/// Сортирует ключевые кадры в хронологическом порядке.
		/// Вызов имеет смысл сразу после добавления новых ключевых кадров.
	
	void OnAnimate(SceneNode::HardPtr node, float dt);
		/// Перегруженный метод базового класса

protected:
	KeyFramedAnimationWeakPtr _animation;
		/// Анимация, которой принадлежит данный канал
	
	///
	/// Ключевой кадр положения.
	///
	struct VectorKey {
		double time;
		math::Vector3 value;
		VectorKey() { }
		VectorKey(double time, const math::Vector3& value) : time(time), value(value) { }
	};
	
	///
	/// Ключевой кадр поворота.
	///
	struct QuaternionKey {
		double time;
		math::Quaternion value;
		QuaternionKey() { }
		QuaternionKey(double time, const math::Quaternion& value) : time(time), value(value) { }
	};
	
	///
	/// Ключевой кадр трансформации.
	///
	struct TransformKey {
		double time;
		math::Matrix4 value;
		TransformKey() { }
		TransformKey(double time, const math::Matrix4& value) : time(time), value(value) { }
	};
	
	typedef std::vector<VectorKey> PositionKeys;
	
	typedef std::vector<QuaternionKey> RotationKeys;
	
	typedef std::vector<VectorKey> ScalingKeys;
	
	typedef std::vector<TransformKey> TransformKeys;
	
	boost::shared_ptr<PositionKeys> _positionKeys;
		/// Ключи положения
	
	boost::shared_ptr<RotationKeys> _rotationKeys;
		/// Ключи поворота
	
	boost::shared_ptr<ScalingKeys> _scalingKeys;
		/// Ключи масштабирования
	
	boost::shared_ptr<TransformKeys> _transformKeys;
		/// Ключи трансформации
	
	Behaviour _preState;
		/// Поведение анимации до выполнения первого кадра
	
	Behaviour _postState;
		/// Поведение анимации после выполнения последнего кадра
};

inline KeyFramedAnimationHardPtr KeyFramedAnimationChannel::GetAnimation() const {
	return _animation.lock();
}
	
inline void KeyFramedAnimationChannel::SetAnimation(KeyFramedAnimationHardPtr animation) {
	_animation = animation;
}

} // namespace SceneGraph

#endif // __KEYFRAMEDANIMATIONCHANNEL_H__
