from serialplot import SerialPlotUnpack
import numpy as np
import matplotlib.pyplot as plt
import logging

logging.basicConfig(level = logging.DEBUG)

if __name__ == '__main__':
  data = SerialPlotUnpack('spdctltuning.csv')  
  dt = 1.0e-3
  ifbk = data[:,0] * 1.0e-3
  spd = data[:,3] * 0.1 * np.pi / 180.
  ss_spd = np.average(spd[-500:])
  ss_ifbk = np.average(ifbk[-500:])
  k_motor = 0.10369
  logging.debug('Steady state speed [rpm]: {}'.format(ss_spd * 180.0 / np.pi / 6.0))
  logging.debug('Steady state speed [rad/s]: {}'.format(ss_spd))
  logging.debug('Steady state current [A]: {}'.format(ss_ifbk))
  kf_motor = k_motor * ss_ifbk / ss_spd
  logging.debug('Estimated friction: {}'.format(kf_motor))
  j_motor = np.sum(k_motor * ifbk - kf_motor * spd) * dt / ss_spd
  logging.debug('Estimated inertia: {}'.format(j_motor))
