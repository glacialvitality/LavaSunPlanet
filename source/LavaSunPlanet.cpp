#include "LavaSunPlanet.h"
#include "Game/Util/ActorAnimUtil.h"
#include "Game/Util/ModelUtil.h"

LavaSunPlanet::LavaSunPlanet(const char* pName) : LiveActor(pName) {
    mRotator = nullptr;
    mObjName = nullptr;
    mLodCtrl = nullptr;
}

void LavaSunPlanet::control() {
    if (mRotator != nullptr) {
        mRotator->movement();
    }

    mLodCtrl->update();
}

void LavaSunPlanet::calcAndSetBaseMtx() {
    if (mRotator == nullptr) {
        LiveActor::calcAndSetBaseMtx();
    } else {
        TPos3f mtx;
        mtx.setInline(mRotator->getRotateMtx());
        //mtx.mMtx[0][3] = mTranslation.x;
        //mtx.mMtx[1][3] = mTranslation.y;
        //mtx.mMtx[2][3] = mTranslation.z;
        //MR::setMtxTrans(mtx, mTranslation);
        mtx.setTrans(mTranslation);
        MR::setBaseTRMtx(this, mtx);
    }
}

void LavaSunPlanet::init(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);
    MR::getObjectName(&mObjName, rIter);
    MR::processInitFunction(this, rIter, false); //initModelManagerWithAnm(mObjName, nullptr, true);
    ProjmapEffectMtxSetter* planetEffect = MR::initDLMakerProjmapEffectMtxSetter(this);
    MR::newDifferedDLBuffer(this);
    MR::connectToScenePlanet(this);
    initHitSensor(1);
    MR::initCollisionParts(this, mObjName, MR::addBodyMessageSensorMapObj(this), nullptr);
    MR::setClippingTypeSphereContainsModelBoundingBox(this, 100.0f);
    MR::setClippingFarMax(this);
    mLodCtrl = MR::createLodCtrlPlanet(this, rIter, -1.0f, -1);
    ProjmapEffectMtxSetter* lodEffect = MR::initDLMakerProjmapEffectMtxSetter(mLodCtrl->mModelObjMiddle);

    if (MR::isExistAnim(this, mObjName)) {
        MR::tryStartAllAnim(this, mObjName);
    } else if (!MR::isExistEffectTexMtx(this)) {
        calcAnim();
        MR::offCalcAnim(this);
    }

    if (MR::isEqualString(mObjName, "LavaRotatePlanet")) {
        mRotator = new MapPartsRotator(this);
        mRotator->init(rIter);
        mRotator->start();
        mLodCtrl->syncJointAnimation();
    }

    makeActorAppeared();
    planetEffect->updateMtxUseBaseMtx();
    lodEffect->updateMtxUseBaseMtx();
}

LavaSunPlanet::~LavaSunPlanet() {}