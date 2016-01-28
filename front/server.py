from flask import Flask, render_template
import glob
import pymongo
import os
from bson import ObjectId


if 'lastTestSession.txt' not in os.listdir('.'):
	print "The server need that the lastTestSession.txt file be here."
	os.sys.exit(-1)


app = Flask(__name__)


@app.route("/")
def load_data():
	client = pymongo.MongoClient()
	db = client['42cv']
	fd = open('lastTestSession.txt','r')
	lines = fd.readlines()
	line = lines[-1]
	id_collection_test = line.split(',')[0]
	collection_test = db['session_test']
	dbtest = collection_test.find_one({"_id": ObjectId(id_collection_test)})
	files_test = dbtest['image_paths'] 
	files_match = dbtest['result_paths']
	labels_test = dbtest['labels']
	labels_match = dbtest['result_labels']
	session_training_id = dbtest['session_training_id']
	collection_training = db['session_training'] 
	dbtraining = collection_training.find_one({"_id": session_training_id})
	files_training = dbtraining['image_paths']
	labels_training = dbtraining['labels']
	return render_template(	"index.html", 
							files_training = files_training, 
							files_test=files_test,
							files_match=zip(files_test,files_match),
							labels_test = labels_test,
							labels_training = labels_training)


@app.route("/stats")
def	stats():
	return render_template("stats.html", files_stats = ["static/stats/" + x for x in os.listdir("static/stats") if x.endswith(".png")])


if __name__ == "__main__":
	app.run(debug=True)
