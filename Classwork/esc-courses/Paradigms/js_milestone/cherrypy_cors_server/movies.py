import cherrypy
import json
from _movie_database import _movie_database

class MovieController(object):

    def __init__(self, mdb=None):
        if mdb is None:
            self.mdb = _movie_database()
        else:
            self.mdb = mdb
        self.mdb.load_movies('ml-1m/movies.dat')
        self.load_posters('ml-1m/images.dat') 


    def GET(self):
        entries=[]
        for key in self.mdb.get_movies():
            movie=self.mdb.get_movie(key)
            try:
                image=self.posters[int(key)]
            except KeyError as ex:
                image=""
            entries.append({"genres":movie[1], "title":movie[0],
                "result":"success", "id":key, "img": image})
        output = {"movies": entries, "result":"success"}
        return json.dumps(output)

    def POST(self):
        output = {"result":"success"}
        payload = cherrypy.request.body.read()
        myinput = json.loads(payload)
        try:
            title=str(myinput['title'])
            genres=str(myinput['genres'])
            mid=self.mdb.add_movie(title, genres)
            output["id"]=mid
        except KeyError as ex:
            output['result'] = 'error'
            output['message']='bad input'
        return json.dumps(output)

    def DELETE(self):
        self.mdb.delete_all_movies()
        output = {"result":"success"}
        return json.dumps(output)

    def GET_MID(self, mid):
        output = {"result":"success"}
        try:
            image=self.posters[int(mid)]
        except KeyError as ex:
            image=""
        try:
            movie=self.mdb.get_movie(int(mid))
            if movie == None:
                output["result"]="error"
            else:
                output={"genres":movie[1], "title":movie[0],
                    "result":"success", "id":mid, "img": image}
        except KeyError as ex:
            output["result"]="error"
            output["message"]="bad id"
        return json.dumps(output)

    def PUT_MID(self, mid):
        output = {"result":"success"}
        payload = cherrypy.request.body.read()
        myinput = json.loads(payload)
        try:
            title=str(myinput['title'])
            genres=str(myinput['genres'])
            self.mdb.set_movie(int(mid),[title,genres])
        except KeyError as ex:
            output['result'] = 'error'
            output['message']='bad input'
        return json.dumps(output)


    def DELETE_MID(self, mid):
        self.mdb.delete_movie(int(mid))
        output = {"result":"success"}
        return json.dumps(output)
   

    def load_posters(self, posters_file):
        self.posters = {}
        f = open(posters_file)
        for line in f:
            line = line.rstrip()
            components = line.split("::")
            mid = int(components[0])
            #mdb_id = int(components[1])
            img = components[2]
            self.posters.update({mid : img})
        f.close()
