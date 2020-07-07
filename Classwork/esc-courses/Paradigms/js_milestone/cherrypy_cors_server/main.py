import cherrypy

from movies import MovieController
from users import UserController
from votes import VoteController
from ratings import RatingController
from reset import ResetController


from _movie_database import _movie_database

def OptionsController():
	def OPTIONS(self, *args, **kwargs):
		return ""

def CORS():
		cherrypy.response.headers["Access-Control-Allow-Origin"] = "*"
		cherrypy.response.headers["Access-Control-Allow-Methods"] = "GET, PUT, POST, DELETE, OPTIONS"
		cherrypy.response.headers["Access-Control-Allow-Credentials"] = "*"

def start_service():
    dispatcher = cherrypy.dispatch.RoutesDispatcher()

    #instantiate mdb
    mdb_o = _movie_database()

    #instantiate controllers
    movieController = MovieController(mdb=mdb_o)
    userController = UserController(mdb=mdb_o)
    voteController = VoteController(mdb=mdb_o)
    ratingController = RatingController(mdb=mdb_o)
    resetController = ResetController(mdb=mdb_o)
    optionsController = OptionsController


    #connect /movies/ resource
    dispatcher.connect('movie_get', '/movies/', controller=movieController, action='GET', conditions=dict(method=['GET']))
    dispatcher.connect('movie_post', '/movies/', controller=movieController, action='POST', conditions=dict(method=['POST']))
    dispatcher.connect('movie_del', '/movies/', controller=movieController, action='DELETE', conditions=dict(method=['DELETE']))
    #connect /movies/:movie_id resource
    dispatcher.connect('movieid_get', '/movies/:mid', controller=movieController, action='GET_MID', conditions=dict(method=['GET']))
    dispatcher.connect('movieid_put', '/movies/:mid', controller=movieController, action='PUT_MID', conditions=dict(method=['PUT']))
    dispatcher.connect('movieid_del', '/movies/:mid', controller=movieController, action='DELETE_MID', conditions=dict(method=['DELETE']))


    #connect /users/ resource
    dispatcher.connect('user_get', '/users/', controller=userController, action='GET', conditions=dict(method=['GET']))
    dispatcher.connect('user_post', '/users/', controller=userController, action='POST', conditions=dict(method=['POST']))
    dispatcher.connect('user_del', '/users/', controller=userController, action='DELETE', conditions=dict(method=['DELETE']))
    #connect /users/:user_id resource
    dispatcher.connect('userid_get', '/users/:uid', controller=userController, action='GET_UID', conditions=dict(method=['GET']))
    dispatcher.connect('userid_put', '/users/:uid', controller=userController, action='PUT', conditions=dict(method=['PUT']))
    dispatcher.connect('userid_del', '/users/:uid', controller=userController, action='DELETE_UID', conditions=dict(method=['DELETE']))

    #connect /ratings/:movie_id resource
    dispatcher.connect('ratingmid_get', '/ratings/:mid', controller=ratingController, action='GET', conditions=dict(method=['GET']))

    #connect /recommendations/ resource
    dispatcher.connect('rec_del', '/recommendations/', controller=voteController, action='DELETE', conditions=dict(method=['DELETE']))
    #connect /recommendations/:user_id resource
    dispatcher.connect('recuid_get', '/recommendations/:uid', controller=voteController, action='GET', conditions=dict(method=['GET']))
    dispatcher.connect('recuid_put', '/recommendations/:uid', controller=voteController, action='PUT', conditions=dict(method=['PUT']))

    #connect /reset/ resource
    dispatcher.connect('reset_put', '/reset/', controller=resetController, action='PUT', conditions=dict(method=['PUT']))
    #connect /reset/:movie_id resource
    dispatcher.connect('resetmid_put', '/reset/:mid', controller=resetController, action='PUT_MID', conditions=dict(method=['PUT']))

	#options
    dispatcher.connect('movie', '/movies/:mid', controller=OptionsController, action='OPTIONS', conditions=dict(method=['OPTIONS']))
    dispatcher.connect('movies', '/movies/', controller=OptionsController, action='OPTIONS', conditions=dict(method=['OPTIONS']))
    dispatcher.connect('user', '/users/:uid', controller=OptionsController, action='OPTIONS', conditions=dict(method=['OPTIONS']))
    dispatcher.connect('users', '/users/', controller=OptionsController, action='OPTIONS', conditions=dict(method=['OPTIONS']))
    dispatcher.connect('rating', '/movies/:mid', controller=OptionsController, action='OPTIONS', conditions=dict(method=['OPTIONS']))
    dispatcher.connect('ratings', '/movies/', controller=OptionsController, action='OPTIONS', conditions=dict(method=['OPTIONS']))
    dispatcher.connect('recommendation', '/movies/:uid', controller=OptionsController, action='OPTIONS', conditions=dict(method=['OPTIONS']))
    dispatcher.connect('recommendations', '/movies/', controller=OptionsController, action='OPTIONS', conditions=dict(method=['OPTIONS']))
    

    #configuration
    conf = { 'global' : {'server.socket_host': 'student05.cse.nd.edu',
        'server.socket_port': 51025,},
        '/' : {'request.dispatch': dispatcher, 'tools.CORS.on':True} }

    cherrypy.config.update(conf)
    app = cherrypy.tree.mount(None, config=conf)
    cherrypy.quickstart(app)


if __name__ == '__main__':
    cherrypy.tools.CORS = cherrypy.Tool('before_finalize', CORS)
    start_service()

