function Item(){
	this.addToDocument=function(){
		//document.body.appendChild(this.item);
		this.Parent.appendChild(this.item);
	};
}

function Label(parent){
	this.Parent = parent.item;
	this.createLabel=function(text, id){
		this.item = document.createElement("p");
		this.item.setAttribute("id", id);
		this.item.innerHTML = text;
	};
	this.setText = function(text){
		this.item.innerHTML=text;
	};
}

function Button(parent){
	this.Parent = parent.item;
	this.createButton = function(text, id){
		this.item = document.createElement("button")
		this.item.setAttribute("id", id);
		this.item.innerHTML = text;	
	};
	this.addClickEventHandler=function(handler, args){
		this.item.onmouseup = function(){
			handler(args);
		};
	};
}

function Image(parent){
	this.Parent = parent.item;
	this.createImage = function(arc, id){
		this.item = document.createElement("img");
		this.item.setAttribute("id", id);
		this.item.setAttribute("arc", arc);
	};
	this.setImage=function(arc){
		this.item.arc = arc;
	};
}

function Div(parent){
	this.Parent = parent.item;
	this.createDiv = function(_class){
		this.item = document.createElement("div");
		this.item.setAttribute("class", _class);
	};
}

