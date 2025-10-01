import React, {useState} from 'react';

function CardUI()
{
    
    let _ud : any = localStorage.getItem('user_data');
    let ud = JSON.parse(_ud);
    let userId : string = ud.userId;
    let firstName : string = ud.firstName;
    let lastName : string = ud.lastName;

    const [message,setMessage] = useState('');
    const [searchResults,setResults] = useState('');
    const [cardList,setCardList] = useState('');
    const [search,setSearchValue] = React.useState('');
    const [card,setCardNameValue] = React.useState('');

    function handleSearchTextChange( e: any ) : void
    {
        setSearchValue( e.target.value );
    }

    function handleCardTextChange( e: any ) : void
    {
        setCardNameValue( e.target.value );
    }

    async function addCard(event:any) : Promise<void>
    {
	event.preventDefault();
	let obj = {name:card, creatorId: userId};
        let js = JSON.stringify(obj);

	try{
	    const response = await fetch('http://localhost:5000/api/cards/add', {method:'POST',body:js,headers:{'Content-Type': 'application/json'}});
            let txt = await response.text();
	    let res = JSON.parse(txt);
	    if(res.error.length > 0){
	    	setMessage("Card CRUD OP Error: "+res.error);
	    }
	    else{
	        setMessage("Card Added Successfully");
	    }
	} catch(error: any){
	    setMessage(error.toString());
	}
    };

    async function searchCard(event:any) : Promise<void>
    {
        event.preventDefault();
        
	let obj = {name:search, creatorId:userId};
	let js = JSON.stringify(obj);

	try{
	    const response = await fetch('http://localhost:5000/api/cards/search', {method:'GET',body:js,headers:{'Content-Type': 'application/json'}});
	    let txt = await response.text();
	    let res = JSON.parse(txt);
	    let _results = res.cards;
	    let resultText = '';
	    for(let i = 0; i < _results.length; i++){
	        resultText += _results[i];
		if(i < _results.length - 1)
		    resultText += ', ';
	    }
	    setResults('Card(s) have been retrieved');
	    setCardList(resultText);
	} catch(error: any){
	    alert(error.toString());
	    setResults(error.toString());
	}
    };

    return(
      <div id="accessUIDiv">
       <br />
       <input type="text" id="searchText" placeholder="Card To Search For" onChange={handleSearchTextChange} />
       <button type="button" id="searchCardButton" className="buttons" 
           onClick={searchCard}> Search Card </button><br />
       <span id="cardSearchResult">{searchResults}</span>
       <p id="cardList">{cardList}</p><br /><br />
       <input type="text" id="cardText" placeholder="Card To Add" onChange={handleCardTextChange} />
       <button type="button" id="addCardButton" className="buttons" 
          onClick={addCard}> Add Card </button><br />
       <span id="cardAddResult">{message}</span>
     </div>
    );
}

export default CardUI;

