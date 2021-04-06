% J*dw/dt = -kf*w + k*i => Kf=K*i/w
% L*di/dt = -R*i -K*w +Vin => K=(Vin-R*i)/w
Motor_K = (12 - MotorParams.R * 35e-3) / 720;
Motor_Kf = Motor_K * 35e-3 / 720;

% 4*J/Kf = Ts
Motor_J = 30e-3 * Motor_Kf / 4.;
