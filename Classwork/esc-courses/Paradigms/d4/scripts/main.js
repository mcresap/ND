// Initialize Prorotypes
Button.prototype = new Element();
Label.prototype = new Element();
Dropdown.prototype = new Element();

// API Interfacing Functions
function changeText(args) {

    // Initialize Variables
    var index = ['movies', 'ratings'];
    xhr = new Array(index.length);

    // Make Requests Asynchronously
    for (let i = 0; i < index.length; i++) {

        // Build URL + Open Request
        var url = 'http://student04.cse.nd.edu:51002/' + index[i] + '/36';
        xhr[i] = new XMLHttpRequest();
        xhr[i].open('GET', url, true);

        // Setup Error Handler
        xhr.onerror = function (e) {
            console.error(xhr.statusText);
        }

        // Setup Load Handler
        xhr[i].onload = function () {
            args[i].updateText(xhr[i].responseText);
        }

        // Make Request
        xhr[i].send();
    }
}

function voteHandler(dropdown) {
    // Build URL + Open Request
    var url = 'http://student04.cse.nd.edu:51002/recommendations/36';
    xhr = new XMLHttpRequest();
    xhr.open('PUT', url, true);

    // Initialize DOM Label
    var text = new Label();
    text.createLabel(' ', 'theResp');
    text.addToDocument();

    // Setup Error Handler
    xhr.onerror = function (e) {
        console.error(xhr.statusText);
    }

    // Setup Load Handler
    xhr.onload = function () {
        var resp = JSON.parse(xhr.responseText);
        
        if (resp.result == 'success') {
            text.updateText('Your vote was submitted!');
        }
        else {
            text.updateText('Vote submission failed!');
        }
    }

    // Build Payload for Request
    var data = {};
    data.movie_id = '36';
    data.rating  = dropdown.getSelected();
    var json = JSON.stringify(data);

    // Make Request
    xhr.send(json);
}

// Movie Label
var label = new Label();
label.createLabel('which movie?', 'theLabel');
label.addToDocument();

// Rating Label
var rating = new Label();
rating.createLabel('the rating', 'theRating');
rating.addToDocument();

// Button
var runButton = new Button();
runButton.createButton('Click Here', 'theButton');
args = [label, rating];
runButton.addClickHandler(changeText, args);
runButton.addToDocument();

// Vote Label
var vote = new Label();
vote.createLabel('I thought this movie was...', 'theVote');
vote.addToDocument();

// Vote Dropdown
var dropdown = new Dropdown();
menuItems = {
    '1: Absolutely Trash': '1',
    '2: Dirt, But Watchable': '2',
    '3: Eh': '3',
    '4: Pretty Decent TBH': '4',
    '5: Best Movie Ever': '5'
}

dropdown.createDropdown(menuItems, 'theDrop', '5');
dropdown.addToDocument();

// Vote Button
var voteButton = new Button();
voteButton.createButton('Vote', 'voteButton');
voteButton.addClickHandler(voteHandler, dropdown);
voteButton.addToDocument();






