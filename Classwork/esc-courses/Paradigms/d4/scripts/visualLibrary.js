// Element Function
function Element(){
    this.addToDocument = function(){
        document.body.appendChild(this.item);
    };
}

// Button Function
function Button() {

    // Create a New Button
    this.createButton = function(text, id){
        this.item = document.createElement("button");
        this.item.setAttribute("id", id);
        var itemText = document.createTextNode(text);
        this.item.appendChild(itemText);
    }

    // Add onClick Event Handler
    this.addClickHandler = function(handler, args){
        this.item.onmouseup = function () {
            handler(args); 
        }; 
    } 
}

// Label Function
function Label() {

    // Create a New Label
    this.createLabel = function (text, id) {
        this.item = document.createElement('p');
        this.item.setAttribute('id', id);
        this.item.innerHTML = text;
    };

    // Update Label Text
    this.updateText = function (text) {
        this.item.innerHTML = text;
    };
}

// Dropdown Function
function Dropdown() {

    // Create a New Dropdown
    this.createDropdown = function (dict, id, selected) {
        this.item = document.createElement('select');
        this.item.setAttribute('id', id);

        // Add All Dropdown Options
        for (item in dict) {
            this.item.options[this.item.options.length] = new Option(item, dict[item]);
        };

        // Update Default Selected
        this.item.value = selected;
    };

    // Return Selected Item
    this.getSelected = function () {
        return this.item.value;
    };
}