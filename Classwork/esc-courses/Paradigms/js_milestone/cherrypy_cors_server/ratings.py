import cherrypy
import json

from _movie_database import _movie_database

class RatingController(object):
    def __init__(self, mdb=None):
        if mdb is None:
            self.mdb = _movie_database()
        else:
            self.mdb = mdb

        self.mdb.load_ratings('ml-1m/ratings.dat')

    def GET(self, mid):
        output={"result":"success"}
        mid=int(mid)
        rating=self.mdb.get_rating(mid)
        if rating==0:
            output["result"]="error"
        else:
            output["movie_id"]=mid
            output["rating"]=rating
        return json.dumps(output)


