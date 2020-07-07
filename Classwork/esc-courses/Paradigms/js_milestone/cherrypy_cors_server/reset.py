import cherrypy
import json

from _movie_database import _movie_database

class ResetController(object):
    def __init__(self, mdb=None):
        if mdb is None:
            self.mdb = _movie_database()
        else:
            self.mdb = mdb

    def PUT(self):  # PUT on /reset/
        output = {'result':'success'}
        data = json.loads(cherrypy.request.body.read().decode())

        try:
            self.mdb.load_movies('ml-1m/movies.dat')
            self.mdb.load_users('ml-1m/users.dat')
            self.mdb.load_ratings('ml-1m/ratings.dat')
        except Exception as ex:
            output['result'] = 'error'
            output['message'] = str(ex)

        return json.dumps(output)

    def PUT_MID(self, mid):  # PUT on /reset/:movie_id
        output = {'result':'success'}
        mid = int(mid)

        try:
            data = json.loads(cherrypy.request.body.read())
            mdb_tmp = _movies_database()
            mdb_tmp.load_movies('ml-1m/movies.dat')
            movie = mdb_tmp.get_movie(mid)
            self.mbd.set_movie(mid, movie) #also set genre
        except Exception as ex:
            output['result'] = 'error'
            output['message'] = str(ex)

        return json.dumps(output)


