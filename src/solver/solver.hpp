#pragma once

class Solver
{
public:
    Solver() {}
    virtual ~Solver() {}

    virtual void update(float dt)
    {
        for (unsigned int i = 0; i < m_steps; ++i)
        {
            update_step(dt);
        }
    }
    
    void setSteps(unsigned int steps) { m_steps = steps; }

protected:
    virtual void update_step(float dt) {}

protected:
    unsigned int m_steps = 1;
};
