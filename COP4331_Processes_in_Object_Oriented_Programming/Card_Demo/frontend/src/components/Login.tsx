import React, {useState} from 'react';

function Login()
{
  const [message, SetMessage] = useState('');
  const [username, setUserName] = React.useState('');
  const [password, setPassword] = React.useState('');
  
  
  function handleSetUserName( e: any) : void {
    setUserName(e.target.value);
  };
  
  function handleSetPassword(e: any) : void{
    setPassword(e.target.value);
  };
  
  async function doLogin(event:any) : Promise<void>
  {
    event.preventDefault();

    var obj = {username:username, password:password};
    var js = JSON.stringify(obj);
    try{
      const response = await fetch('http://localhost:5000/api/login', {method:'POST', body:js, headers:{'Content-Type':'application/json'}});
      var res = JSON.parse(await response.text());
     if(res.error.length > 0){
     	setMessage(res.error);
     }else{
       var user = {userId:res.userId, firstName:res.firstName, lastName:res.lastName};
       localStorage.setItem('user_data', JSON.stringify(user));
       setMessage('');
       window.location.href = '/cards';
     
     }
    
    } catch(error:any){
      alert(error.toString());
      return;
    }
  };
  
    return(
      <div id="loginDiv">
        <span id="inner-title">PLEASE LOG IN</span><br />
        <input type="text" id="username" placeholder="Username" onChange={handleSetUserName} /><br />
        <input type="password" id="password" placeholder="Password" onChange={handleSetPassword} /><br />
        <input type="submit" id="loginButton" className="buttons" value = "Do It"
          onClick={doLogin} />
        <span id="loginResult">{message}</span>
     </div>
    );
};

export default Login;

