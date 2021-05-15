import json
import uuid
import redis
import flask
import datetime

app = flask.Flask(__name__)
rdb = redis.Redis(host="localhost", port=6379, db=0)
rdb.config_set("protected-mode", "no")

my_keys = []

@app.route("/")
def index():
    try:
        with open("/code/tests/run.mos") as f:
            data = f.read()
    except Exception as e:
        pass
    return flask.render_template("index.html", data=data)


@app.route("/show/<string:key>")
def show(key):
    labels, values = [], []
    data = rdb.get(key.encode())
    if not data:
        flask.abort(404, description="Resource not found")
    data = json.loads(data)
    for item in data["result"]:
        labels.append(float(item[0]))
        values.append(float(item[1]))
    return flask.render_template("show.html", data=data, labels=labels, values=values)


@app.route("/api/simulate", methods=["POST"])
def simulate():
    _id = str(uuid.uuid4())
    text = flask.request.json.get("simulateText")
    if not text:
        return "404"
    data = json.dumps(
        {
            "id": _id,
            "date": datetime.datetime.now().strftime("%H:%M:%S %d-%m-%y"),
            "params": text,
            "result": [],
            "simulation_time": 0.0,
        }
    )
    my_keys.append(_id)
    rdb.set(_id, data)
    rdb.rpush("queue:jobs", data)
    return flask.redirect(flask.url_for("index"))


@app.route("/api/simulations")
def simulations():
    data = {}
    try:
        for key in my_keys:
            values = json.loads(rdb.get(key))
            data[key] = values
    except Exception as e:
        pass
    return flask.jsonify(data)


@app.route("/api/download/<string:key>")
def download(key):
    try:
        data = json.loads(rdb.get(key))
    except Exception as e:
        flask.abort(500, description=str(e))
    csv = '"time","x"\n'  # Add CSV header
    csv += "\n".join(f"{item[0]},{item[1]}" for item in data["result"])
    return flask.Response(
        csv,
        mimetype="text/csv",
        headers={"Content-disposition": f"attachment; filename={data['id']}.csv"},
    )


@app.route("/api/delete/<string:key>")
def delete(key):
    try:
        rdb.delete(key)
        my_keys.remove(key)
    except Exception as e:
        flask.abort(500, description=str(e))
    return flask.redirect(flask.url_for("index"))
