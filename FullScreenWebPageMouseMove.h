// ---------------------------------------------------------------------------

#ifndef FullScreenWebPageMouseMoveH
#define FullScreenWebPageMouseMoveH
// ---------------------------------------------------------------------------
__interface IMouseMove : public IUnknown {
	virtual void MouseMoveEvent() = 0;
};
#endif
