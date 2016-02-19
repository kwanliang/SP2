#ifndef BOSS1_H
#define BOSS1_H

#include "Vector3.h"

class Boss1 {
public:
    int HP;

    Boss1();
    ~Boss1();
    virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
    virtual void Update(double dt);

    void SlimeSplit();
};

#endif