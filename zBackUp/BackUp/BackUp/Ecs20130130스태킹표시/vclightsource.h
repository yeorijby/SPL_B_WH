// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CVcLightSource wrapper class

class CVcLightSource : public COleDispatchDriver
{
public:
	CVcLightSource() {}		// Calls COleDispatchDriver default constructor
	CVcLightSource(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcLightSource(const CVcLightSource& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	float GetIntensity();
	void SetIntensity(float newValue);
	float GetX();
	void SetX(float newValue);
	float GetY();
	void SetY(float newValue);
	float GetZ();
	void SetZ(float newValue);
	void Set(float X, float Y, float Z, float Intensity);
};
