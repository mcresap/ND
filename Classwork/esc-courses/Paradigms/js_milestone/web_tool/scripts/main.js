MID = "25"

function changeMovie(args){
    Title=args[0];
    Image=args[1];
    Rating=args[2];

    var xhr = new XMLHttpRequest()
    xhr.open("GET", "http://student05.cse.nd.edu:51025/movies/"+MID, true)
    xhr.onload = function(e) { 
        console.log(xhr.responseText);
        title = JSON.parse(xhr.responseText)['title'];
        Title.setText(title);
        image = JSON.parse(xhr.responseText)['img'];
        image.setImage("http://student05.cse.nd.edu/skumar5/images/"+img)
    }
    xhr.onerror = function(e) { 
        console.error(xhr.statusText);
    }
    xhr.send(null)
    
    var Rxhr = new XMLHttpRequest()
    Rxhr.open("GET", "http://student05.cse.nd.edu:51025/ratings/"+MID, true)
    Rxhr.onload = function(e) {
        console.log(Rxhr.responseText);
        rating=JSON.parse(Rxhr.responseText)['rating'];
        Rating.setText(rating);
    }
    Rxhr.onerror = function(e) { 
        console.error(Rxhr.statusText);
    }
    Rxhr.send(null)
};

function newMovie(args){ 
    var xhr = new XMLHttpRequest()
    xhr.open("GET", "http://student05.cse.nd.edu:51025/recommendations/25", true)
    xhr.onload = function(e) { 
        console.log(xhr.responseText);
        MID = JSON.parse(xhr.responseText)['mid'];
        changeMovie(args);
    }
    xhr.onerror = function(e) { 
        console.error(xhr.statusText);
    }
    xhr.send(null)
  
}

function vote(vote_value){
    payload = {
        "movie_id": "25",
        "rating": vote_value
    }
    payload = JSON.stringify(payload)
    var xhr = new XMLHttpRequest()
    xhr.open("PUT", "http://student04.cse.nd.edu:51025/recommendations/25", true)
    xhr.onload = function(e) { 
        console.log(xhr.responseText);
        newMovie();
    }
    xhr.onerror = function(e) { 
        console.error(xhr.statusText);
    }
    xhr.send(payload)
};

body = {'item': document.body};

Label.prototype = new Item();
Button.prototype= new Item();
Div.prototype = new Item();
Image.prototype = new Item();

title = new Label(body);
title.createLabel("title", "titleLabel");
title.addToDocument();

container = new Div(body);
container.createDiv("container");
container.addToDocument();

left = new Div(container);
left.createDiv("leftPanel");
left.addToDocument();

right = new Div(container);
right.createDiv("rightPanel");
right.addToDocument();

center = new Div(container);
center.createDiv("centerPanel");
center.addToDocument();

image = new Image(centerPanel);
image.createImage("/default.jpg", "movieimage");
image.addToDocument();

rating = new Label(body);
rating.createLabel("rating", "theRating");
rating.addToDocument();

args = [title, image, rating];
changeMovie(args);

voteUp = new Button(leftPanel);
voteUp.createButton("Up", "VoteUp");
voteUp.addClickEventHandler(vote, 5);
voteUp.addToDocument();

voteDown = new Button(rightPanel)
voteDown.createButton("Down", "VoteDown");
voteDown.addClickEventHandler(vote, 1);
voteDown.addToDocument();


