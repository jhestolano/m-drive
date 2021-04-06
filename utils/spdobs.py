import numpy as np
import matplotlib.pyplot as plt
import logging
from serialplot import SerialPlotUnpack

logging.basicConfig(level = logging.DEBUG)

Ts = 10e-3

def CalcSpeed(pos_a):
  vest_a = np.array([])
  pest_a = np.array([])
  bw = 50.
  kp = 2. * bw
  ki = kp ** 2 / 4.
  posest = pos_a[0]
  vest = 0.
  logging.debug('Observer gains -> Kp: {}, Ki: {}'.format(kp, ki))
  for pos in pos_a:
    logging.debug('poserr: {}'.format(pos - posest))
    dv = ki * (pos - posest)
    logging.debug('dv: {}'.format(dv))
    vest = dv * Ts + vest
    dp = vest + kp * (pos - posest)
    logging.debug('dp: {}'.format(dp))
    posest = dp * Ts + posest
    logging.debug('posest: {}'.format(posest))
    vest_a = np.append(vest_a, vest)
    pest_a = np.append(pest_a, posest)
  plt.plot(vest_a)
  plt.plot(np.diff(pos_a) / Ts, 'r--')
  plt.show()
  plt.plot(pos_a)
  plt.plot(pest_a, 'r--')
  plt.show()

if __name__ == '__main__':
  rawdata = SerialPlotUnpack('motorpos.csv')
  CalcSpeed(rawdata[:, 2] * 0.1)
