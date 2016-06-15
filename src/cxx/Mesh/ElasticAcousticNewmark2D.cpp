#include <Mesh/ElasticAcousticNewmark2D.h>

void ElasticAcousticNewmark2D::advanceField(double dt) {

  double pre_factor_acceleration = (1.0/2.0) * dt;
  double pre_factor_displacement = (1.0/2.0) * (dt * dt);

  VecAXPBYPCZ(mFields["vx"]->glb, pre_factor_acceleration, pre_factor_acceleration, 1.0,
              mFields["ax"]->glb, mFields["ax_"]->glb);
  VecAXPBYPCZ(mFields["vy"]->glb, pre_factor_acceleration, pre_factor_acceleration, 1.0,
              mFields["ay"]->glb, mFields["ay_"]->glb);
  VecAXPBYPCZ(mFields["v"]->glb, pre_factor_acceleration, pre_factor_acceleration, 1.0,
              mFields["a"]->glb, mFields["a_"]->glb);

  VecAXPBYPCZ(mFields["ux"]->glb, dt, pre_factor_displacement, 1.0,
              mFields["vx"]->glb, mFields["ax"]->glb);
  VecAXPBYPCZ(mFields["uy"]->glb, dt, pre_factor_displacement, 1.0,
              mFields["vy"]->glb, mFields["ay"]->glb);
  VecAXPBYPCZ(mFields["u"]->glb, dt, pre_factor_displacement, 1.0,
              mFields["v"]->glb, mFields["a"]->glb);

  VecCopy(mFields["ax"]->glb, mFields["ax_"]->glb);
  VecCopy(mFields["ay"]->glb, mFields["ay_"]->glb);
  VecCopy(mFields["a"]->glb, mFields["a_"]->glb);

  double max_ux, max_u;
  VecMax(mFields["ux"]->glb, NULL, &max_ux); VecMax(mFields["u"]->glb, NULL, &max_u);
  std::cout << "MAX: " << max_ux << ' ' << max_u << std::endl;

}

void ElasticAcousticNewmark2D::applyInverseMassMatrix() {

  if (mFields.find("mi") == mFields.end()) {
    registerFieldVectors("mi");
    VecCopy(mFields["m"]->glb, mFields["mi"]->glb);
    VecReciprocal(mFields["mi"]->glb);
  }

  VecPointwiseMult(mFields["ax"]->glb, mFields["mi"]->glb,
                   mFields["ax"]->glb);
  VecPointwiseMult(mFields["ay"]->glb, mFields["mi"]->glb,
                   mFields["ay"]->glb);
  VecPointwiseMult(mFields["a"]->glb, mFields["mi"]->glb,
                   mFields["a"]->glb);

}
