import cherrypy
import json

from _movie_database import _movie_database

class UserController(object):
    def __init__(self, mdb=None):
        if mdb is None:
            self.mdb = _movie_database()
        else:
            self.mdb = mdb
        
        self.mdb.load_users('ml-1m/users.dat')


    def GET(self):
        output={"result":"success"}
        users=[]
        for uid in self.mdb.get_users():
            user=self.mdb.get_user(uid)
            users.append({"zipcode": user[3], "age":user[1],
                "gender":user[0], "id":uid,"occupation":user[2]})
        output["users"]=users
        return json.dumps(output)

    def POST(self):
        output = {"result":"success"}
        payload = cherrypy.request.body.read()
        myinput = json.loads(payload)
        try:
            zipcode=myinput["zipcode"]
            gender=myinput["gender"]
            age=myinput["age"]
            occ=myinput["occupation"]
            uid = self.mdb.add_user(gender, age, occ, zipcode)
            output["id"]= uid
        except KeyError as ex:
            output["result"]="error"
        return json.dumps(output)


    def DELETE(self):
        output = {"result":"success"}
        self.mdb.delete_all_users()
        return json.dumps(output)


    def GET_UID(self, uid):
        output={"result":"success"}
        user=self.mdb.get_user(int(uid))
        if user == None:
            output["result"]="error"
        else:
            output={"zipcode": user[3], "age":user[1],
                    "gender":user[0], "id":int(uid),
                    "occupation":user[2], "result":"success"}
        return json.dumps(output)

    def PUT(self, uid):
        output = {"result":"success"}
        payload = cherrypy.request.body.read()
        myinput = json.loads(payload)
        try:
            zipcode=myinput["zipcode"]
            gender=myinput["gender"]
            age=myinput["age"]
            occ=myinput["occupation"]
            uid = self.mdb.set_user(int(uid),[gender, age, occ, zipcode])
        except KeyError as ex:
            output["result"]="error"
        return json.dumps(output)


    def DELETE_UID(self,uid):
        output = {"result":"success"}
        self.mdb.delete_user(int(uid))
        return json.dumps(output)



