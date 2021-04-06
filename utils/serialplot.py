import sys
import numpy as np
import matplotlib.pyplot as plt
import logging
from scipy import signal

logging.basicConfig(level = logging.DEBUG)

T_SAMPLE = 1.0e-3
# Script is going to search for these signals of interest only.
SIG_NAMES = ['Position', 'Speed', 'Current', 'Voltage']

def SerialPlotUnpack(fname):
  with open(fname) as file:
      rawdata = file.read()
  if len(rawdata) == 0:
      raise Exception('File does not contain data!')
  ''' Element (0) contains signal lables. '''
  labels = rawdata.splitlines()[0].split(',')
  rawdata = rawdata.splitlines()[1:]
  rawdata = map(lambda s: s.split(','), rawdata)
  logging.debug('Raw data: {}'.format(rawdata))
  logging.debug('Data: {}'.format(rawdata))
  data =  np.array(list(rawdata)).astype('float')
  return {'labels': labels, 'data': data}

def SerialPlotShow(data):
  for i, label in enumerate(SIG_NAMES):
    plt.subplot(2, 2, i + 1)
    plt.plot(data['data'][:, data['labels'].index(label)])
    plt.title(label)
    plt.grid()
  plt.show()
  
def SerialPlotIdentify(signals):
  ''' Remove voltage from output vector. '''
  labels = signals['labels']
  data = signals['data']  
  speedidx = labels.index('Speed')
  curridx = labels.index('Current')
  voltidx = labels.index('Voltage')
  yvec = np.array([data[:, speedidx], data[:, curridx]]).T
  yvec = yvec[1:, :]
  xvec = np.array([data[:, speedidx], data[:, curridx], data[:, voltidx]]).T
  xvec = xvec[: -1, :]
  logging.debug('XVec dims: {}'.format(xvec.shape))
  logging.debug('YVec dims: {}'.format(yvec.shape))
  params, res, rank, s = np.linalg.lstsq(xvec, yvec, rcond = None)
  logging.debug('Params: {}'.format(params))
  logging.debug('Params Dims: {}'.format(params.shape))
  yhat = xvec.dot(params)
  amtx = params[:yhat.shape[1], :].T 
  bmtx = params[-1, :].reshape(1, 2)
  cmtx = np.eye(amtx.shape[0])
  dmtx = np.zeros([2, 1])
  logging.debug('A-Mat Shape: {}'.format(amtx.shape))
  logging.debug('B-Mat Shape: {}'.format(bmtx.T.shape))
  logging.debug('C-Mat Shape: {}'.format(cmtx.shape))
  logging.debug('D-Mat Shape: {}'.format(dmtx.shape))
  sys = signal.StateSpace(amtx, bmtx.T, cmtx, dmtx, dt = T_SAMPLE)
  u = data[:, voltidx]
  t = np.arange(len(u)) * T_SAMPLE
  x0 = xvec[0, :-1]
  yhat = np.squeeze(signal.dlsim(sys, u, x0 = x0)[-1])
  ylabels = [labels[speedidx], labels[curridx]]
  for i in range(yhat.shape[1]):
    plt.subplot(yhat.shape[1], 1, i + 1)
    plt.plot(yvec[:, i])
    plt.plot(yhat[:, i], 'r--', LineWidth = 0.9)
    plt.title(ylabels[i])
    plt.legend(['Actual', 'Estimate'])
    plt.grid()
  plt.show()

if __name__ == '__main__':
  fname = sys.argv[1]
  data = SerialPlotUnpack(fname)
  logging.debug('{}'.format(data))
  SerialPlotShow(data)
  SerialPlotIdentify(data)
