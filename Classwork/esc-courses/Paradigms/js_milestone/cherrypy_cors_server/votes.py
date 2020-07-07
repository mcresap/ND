import cherrypy
import json

from _movie_database import _movie_database

class VoteController(object):
    def __init__(self, mdb=None):
        if mdb is None:
            self.mdb = _movie_database()
        else:
            self.mdb = mdb
    
        self.mdb.load_ratings('ml-1m/ratings.dat')

    def DELETE(self):
        output={"result":"success"}
        self.mdb.ratings.clear()
        return json.dumps(output)

    def GET(self, uid):
        output={"result":"success"}
        mid = self.mdb.get_highest_rated_movie(int(uid))
        if mid == None:
            output["result"]="error"
        else:
            output["movie_id"]=mid
        return json.dumps(output)

        

    def PUT(self, uid):
        output = {"result":"success"}
        payload = cherrypy.request.body.read()
        myinput = json.loads(payload)
        try:
            mid=myinput["movie_id"]
            rating=myinput["rating"]
            self.mdb.set_user_movie_rating(int(uid), int(mid), int(rating))
        except KeyError as ex:
            output["result"]="error"
        return json.dumps(output)

