#include "input.h"

#include <vector>

#ifdef __GNUC__
#include <parallel/algorithm>
#else
#include <algorithm>
#endif

/***********************************************************************************/
template<typename T>
struct InputInstance : std::pair<T, Input::InputState> {

	using base_class = std::pair<T, Input::InputState>;

	inline constexpr InputInstance(const T value) : base_class(value, Input::InputState::Invalid) {}
	inline constexpr InputInstance(const T value, const Input::InputState state) : base_class(value, state) {}

	inline auto operator==(const InputInstance &rhs) const noexcept {
		return this->first == rhs.first;
	}
};

/***********************************************************************************/
// Instance types
using KeyInstance = InputInstance<Qt::Key>;
using ButtonInstance = InputInstance<Qt::MouseButton>;

// Container types
using KeyContainer = std::vector<KeyInstance>;
using ButtonContainer = std::vector<ButtonInstance>;

static KeyContainer sg_keyInstances;
static ButtonContainer sg_buttonInstances;
static QPoint sg_mouseCurrPosition;
static QPoint sg_mousePrevPosition;
static QPoint sg_mouseDelta;

/***********************************************************************************/
static inline auto FindKey(const Qt::Key value) {
#ifdef __GNUC__
	return __gnu_parallel::find(sg_keyInstances.begin(), sg_keyInstances.end(), value);
#else
	return std::find(sg_keyInstances.begin(), sg_keyInstances.end(), value);
#endif
}

/***********************************************************************************/
static inline auto FindButton(const Qt::MouseButton value) {
#ifdef __GNUC__
	return __gnu_parallel::find(sg_buttonInstances.begin(), sg_buttonInstances.end(), value);
#else
	return std::find(sg_buttonInstances.begin(), sg_buttonInstances.end(), value);
#endif
}

/***********************************************************************************/
template <typename TPair>
static inline void UpdateStates(TPair& instance) noexcept {
	switch (instance.second) {
	case Input::InputState::Registered:
		instance.second = Input::InputState::Triggered;
		break;
	case Input::InputState::Triggered:
		instance.second = Input::InputState::Pressed;
		break;
	case Input::InputState::Unregistered:
		instance.second = Input::InputState::Released;
		break;
	default:
		break;
	}
}

/***********************************************************************************/
template <typename TPair>
static inline auto CheckReleased(const TPair& instance) -> bool {
	return instance.second == Input::InputState::Released;
}

/***********************************************************************************/
template <typename Container>
static inline void Update(Container& container) {
	using TPair = typename Container::value_type;

	// Remove old data
	const auto remove = std::remove_if(container.begin(), container.end(), &CheckReleased<TPair>);
	container.erase(remove, container.end());

	// Update existing data
#ifdef __GNUC__
	__gnu_parallel::for_each(container.begin(), container.end(), &UpdateStates<TPair>);
#else
	std::for_each(container.begin(), container.end(), &UpdateStates<TPair>);
#endif
}

/***********************************************************************************/
Input::InputState Input::keyState(const Qt::Key key) {
	const auto it = FindKey(key);

	return (it != sg_keyInstances.end()) ? it->second : InputState::Invalid;
}

/***********************************************************************************/
Input::InputState Input::buttonState(const Qt::MouseButton button) {
	const auto it = FindButton(button);

	return (it != sg_buttonInstances.end()) ? it->second : InputState::Invalid;
}

/***********************************************************************************/
QPoint Input::mouseDelta() noexcept {
	return sg_mouseDelta;
}

/***********************************************************************************/
void Input::update() {
	// Update Mouse Delta
	sg_mousePrevPosition = sg_mouseCurrPosition;
	sg_mouseCurrPosition = QCursor::pos();
	sg_mouseDelta = sg_mouseCurrPosition - sg_mousePrevPosition;

	// Update KeyState values
	Update(sg_buttonInstances);
	Update(sg_keyInstances);
}

/***********************************************************************************/
void Input::registerKeyPress(const int key) {
	auto it = FindKey(static_cast<Qt::Key>(key));

	if (it == sg_keyInstances.end()) {
		sg_keyInstances.emplace_back(KeyInstance(static_cast<Qt::Key>(key), InputState::Registered));
	}
}

/***********************************************************************************/
void Input::registerKeyRelease(const int key) {
	const auto it = FindKey(static_cast<Qt::Key>(key));

	if (it != sg_keyInstances.end()) {
		it->second = InputState::Unregistered;
	}
}

/***********************************************************************************/
void Input::registerMousePress(const Qt::MouseButton button) {
	const auto it = FindButton(button);

	if (it == sg_buttonInstances.end()) {
		sg_buttonInstances.emplace_back(ButtonInstance(button, InputState::Registered));
	}
}

/***********************************************************************************/
void Input::registerMouseRelease(const Qt::MouseButton button) {
	const auto it = FindButton(button);

	if (it != sg_buttonInstances.end()) {
		it->second = InputState::Unregistered;
	}
}

/***********************************************************************************/
void Input::reset() noexcept {
	sg_keyInstances.clear();
	sg_buttonInstances.clear();
}
