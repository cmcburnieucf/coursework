import React from 'react';
import {BrowserRouter as Router, Route, Redirect, Switch} from 'react-router-dom';

import logo from './logo.svg';
import './App.css';

import LoginPage from './pages/LoginPage';
import CardPage from './pages/CardPage';

function App() {
  return (
    <Router>
      <Switch>
        <Route path="/" exact>
	  <LoginPage />
	</Route>
	<Route path="/cards" exact>
	  <CardPage />
	</Route>
	<Route path="*">
	  <Redirect to="/" />
	</Route>
      </Switch>
    </Router>
  );
}

export default App;
