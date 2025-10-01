const express = require('express');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const User = require('../models/User');
const router = express.Router();

// Signup route
router.post('/signup', async (req, res) => {
  const { username, password, firstname, lastname } = req.body;
  try {
    const user = new User({ Username:username, Password:password, FirstName:firstname, LastName:lastname });
    await user.save();
    res.status(201).json({ message: 'User created', error: '' });
  } catch (err) {
    res.status(500).json({ error: 'Error creating user: '+err });
  }
});

// Login route
router.post('/login', async (req, res) => {
  const { username, password } = req.body;
  try {
    const user = await User.findOne({ Username:username });
    if (!user) return res.status(400).json({ error: 'User not found' });
    const isMatch = await bcrypt.compare(password, user.password);
    if (!isMatch) return res.status(400).json({ error: 'Invalid credentials' });
    res.json({userId: user._id, firstName: user.FirstName, lastName: user.LastName, error: ''});
  } catch (err) {
    res.status(500).json({ error: 'Error logging in'+err });
  }
});

module.exports = router;
