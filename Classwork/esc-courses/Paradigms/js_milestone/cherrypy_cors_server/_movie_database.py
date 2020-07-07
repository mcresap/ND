class _movie_database:
    
    def __init__(self):
        self.movies  = dict()
        self.users   = dict()
        self.ratings = dict()    
        
    def load_movies(self, movie_file):
        f = open(movie_file)
        for line in f:
            line = line.rstrip()
            components = line.split("::")
            mid = int(components[0])
            mname = components[1]
            genres = components[2]

            self.movies[mid]=[mname, genres]
        f.close()



 #   def print_sorted_movies(self):
 #       self.movies = sorted(self.movies)
 #       for movie in self.movies:
 #           print(movie)

    def get_movie(self, mid):
        if mid in self.movies:
            return self.movies[mid]
        else:
            return None
    
    def delete_all_movies(self):
        self.movies.clear()

    def get_movies(self):
        return self.movies.keys()

    def add_movie(self, title, genre):
        mid = max(self.movies.keys())+1
        self.movies[mid]=[title, genre]
        return mid

    def set_movie(self, mid, titleGenre):
        self.movies[mid]=titleGenre

    def delete_movie(self, mid):
        if mid in self.movies.keys():
            del self.movies[mid]

    def load_users(self, user_file):
        f = open(user_file)
        for line in f:
            line = line.rstrip()
            components = line.split("::")
            uid = int(components[0])
            gender = components[1]
            age = int(components[2])
            occupationcode = int(components[3])
            zipcode = components[4]
            
            self.users[uid]=[gender, age, occupationcode, zipcode]
        f.close()

    def get_user(self, uid):
        if uid in self.users.keys():
            return self.users[uid]
        else:
            return None

    def get_users(self):
        return self.users.keys()

    def set_user(self, uid, mylist):
        self.users[uid]=mylist

    def add_user(self, gender, age, occ, zipcode):
        uid = max(self.users.keys())+1
        self.users[uid]=[gender, age, occ, zipcode]
        return uid

    def delete_user(self, uid):
        del self.users[uid]

    def delete_all_users(self):
        self.users.clear()

    def load_ratings(self, ratings_file):
        self.delete_all_ratings()
        f = open(ratings_file)
        for line in f:
            line = line.rstrip()
            components = line.split("::")
            uid = int(components[0])
            mid = int(components[1])
            rating = int(components[2])

            if mid in self.ratings:
                self.ratings[mid][uid]=rating
            else:
                self.ratings[mid]={uid:rating}
        f.close()

    def get_rating(self, mid):
        if mid in self.ratings.keys():
            return sum(self.ratings[mid].values())/len(self.ratings[mid].values())
        else:
            return 0

    def get_highest_rated_movie(self, uid):
        maxRate = 0
        maxMID = None
        for mid in self.ratings.keys():
            score = self.get_rating(mid)
            if uid in self.ratings[mid]:
                continue
            if score == maxRate:
                if mid < maxMID or maxMID==None:
                    maxMID = mid
            elif score > maxRate:
                maxRate = score
                maxMID = mid
        return maxMID

    def set_user_movie_rating(self, uid, mid, rating):
        if mid not in self.ratings:
            self.ratings[mid]={uid : rating}
        else:
            self.ratings[mid][uid]=rating

    def get_user_movie_rating(self, uid, mid):
        if mid not in self.ratings or uid not in self.ratings[mid]:
            return None
        else:
            return self.ratings[mid][uid]

    def delete_all_ratings(self):
        self.ratings.clear()


#if __name__ == "__main__":
      # mdb = _movie_database()

       #### MOVIES ########
      # mdb.load_movies('ml-1m/movies.dat')



