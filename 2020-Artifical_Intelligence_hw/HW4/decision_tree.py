import numpy as np
import treePlotter
import pandas as pd

def binarySplitDataSet(dataset,feature,value):
    matLeft = dataset.loc[dataset[feature] <= value]
    matRight = dataset.loc[dataset[feature] > value]
    return matLeft,matRight
    
def regressLeaf(dataset):
    count0 = len(dataset[dataset['Species'] == 0])
    count1 = len(dataset[dataset['Species'] == 1])
    count2 = len(dataset[dataset['Species'] == 2])

    weights = [count0, count1, count2]
    return np.argmax(weights)


def regressErr(dataset):
    #每個種類的機率平方和/劃分節點
    count0 = len(dataset[dataset['Species'] == 0])
    count1 = len(dataset[dataset['Species'] == 1])
    count2 = len(dataset[dataset['Species'] == 2])
    count = len(dataset)
    gini = 1 - np.square(np.true_divide(count0, count)) - np.square(np.true_divide(count1, count)) - np.square(np.true_divide(count2, count))
    gini = np.true_divide(gini, 2)
    return gini

def chooseBestSplit(dataset,leafType=regressLeaf,errType=regressErr,threshold=(0.01,4)):
    thresholdErr = threshold[0];thresholdSamples = threshold[1]
    #當數據中輸出值都相等時，feature = None,value = 輸出值的均值（葉節點）
    if len(set(dataset['Species'].T.tolist())) == 1:
        return None,leafType(dataset)
    Err = errType(dataset)
    bestErr = np.inf; bestFeatureIndex = 0; bestFeatureValue = 0
    featureNames = dataset.columns[0:-1].tolist()
    for featureName in featureNames:
        for featurevalue in dataset[featureName].tolist():
            matLeft,matRight = binarySplitDataSet(dataset,featureName,featurevalue)
            if (np.shape(matLeft)[0] < thresholdSamples) or (np.shape(matRight)[0] < thresholdSamples):
                continue
            temErr = errType(matLeft) + errType(matRight)
            if temErr < bestErr:
                bestErr = temErr
                bestFeatureIndex = featureName
                bestFeatureValue = featurevalue
    #檢驗在所選出的最優劃分特徵及其取值下，劃分的左右數據集的樣本數是否小於閾值，若是，則不適合劃分
    if (Err - bestErr) < thresholdErr:
        return None,leafType(dataset)
    matLeft,matRight = binarySplitDataSet(dataset,bestFeatureIndex,bestFeatureValue)
    
    #檢驗在所選出的最優劃分特徵及其取值下，劃分的左右數據集的樣本數是否小於閾值，若是，則不適合劃分
    if (np.shape(matLeft)[0] < thresholdSamples) or (np.shape(matRight)[0] < thresholdSamples):
        return None,leafType(dataset)
    return bestFeatureIndex,bestFeatureValue


def createCARTtree(dataset,leafType=regressLeaf,errType=regressErr,threshold=(1,4)):
    feature,value = chooseBestSplit(dataset,leafType,errType,threshold)
    
#當不滿足閾值或某一子數據集下輸出全相等時，返回葉節點
    if feature == None: return value
    returnTree = {}
    leftSet,rightSet = binarySplitDataSet(dataset,feature,value)
    returnTree[feature] = {}
    returnTree[feature]['<=' + str(value) + 'contains' + str(len(leftSet))] = createCARTtree(leftSet,leafType,errType,threshold)
    returnTree[feature]['>' + str(value) + 'contains' + str(len(rightSet))] = createCARTtree(rightSet,leafType,errType,threshold)
    return returnTree
if __name__ == '__main__':

    data = pd.read_csv("iris.csv")
    data = data.sample(frac=1.0)
    data = data.reset_index()
    deleteColumns = [0,1]
    data.drop(data.columns[deleteColumns], axis=1, inplace=True)

    trainDataset = data.loc[0:99]
    validationDataset = data.loc[100:129]
    testDataset = data.loc[130:-1]

    cartTree = createCARTtree(trainDataset,threshold=(0.01,4))
    treePlotter.createPlot(cartTree)