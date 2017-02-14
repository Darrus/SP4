#ifndef LIGHT_BASE_H
#define LIGHT_BASE_H

class LightBase
{
public:
	LightBase();
	virtual ~LightBase();

	virtual void Update(double _dt);
	virtual void UpdateUniforms();

private:
};

#endif // LIGHT_BASE_H