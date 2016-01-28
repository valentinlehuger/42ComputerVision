import pandas as pd
import glob
import sys

if (len(sys.argv) < 2):
	print "Error need a directory argument"
	sys.exit()

path_training = glob.glob("./"+sys.argv[1]+"/training/*/*")
labels_training = [x.split("/")[-2] for x in path_training]
df = pd.DataFrame()
df["path"] = path_training
df["label"] = labels_training
df.to_csv("./csv_training.csv", sep=",", index=False)
