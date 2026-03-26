#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void energyDataUpdated(const Model::EnergyData& data) {}

    virtual void mainDataUpdated(const Model::MainScreenData& data) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
