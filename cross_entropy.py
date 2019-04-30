from sklearn.metrics import log_loss
from sklearn.preprocessing import LabelBinarizer
from math import log
import numpy as np

y_true = [1,4,5]
y_pred = [  [0.1, 0.6, 0.3, 0,0,0,0,0,0,0],
            [0.1, 0.3, 0.2, 0,0.5,0,0,0,0,0],
            [0.6, 0.3, 0, 0,0,0.1,0,0,0,0]]
labels = [0,1,2,3,4,5,6,7,8,9]


def BinaryLable(labels):
    '''
    标签二值化
    '''
    global y_true
    lb = LabelBinarizer()
    lb.fit(labels)
    return lb.transform(y_true)

N = len(y_true)
K = len(labels)

eps = 1e-15
loss = 0

Blable = BinaryLable(labels)

for i in range(N):
    for k in range(K):
        if y_pred[i][k] < eps:
            y_pred[i][k] = eps
        if y_pred[i][k] > 1-eps:
            y_pred[i][k] = 1-eps
        loss -= Blable[i][k]*log(y_pred[i][k])

loss /= N

print(loss)


