const express = require('express');
const router = express.Router();
const Card = require('../models/Card');

//Add New Card
router.post('/add', async(req, res) => {
    const {name, creatorId} = req.body;
    try{
	const card = new Card({Name:name, UserID:creatorId});
	await card.save();
	res.status(201).json({error: '', card});
    } catch(err) {
	res.status(500).json({error:'Error Adding New Card: '+err});
    }
});

//Search for Cards
router.get('/search', async(req, res) => {
    const {name, creatorId} = req.body;
    try{
        const cards = await Card.find({Name:{$regex:name.trim(), $options:'i'}, UserID:creatorId});
        if(cards.length === 0){
	    return res.status(404).json({error: 'No Cards Found'});
        }
        res.json({error: '', cards});
    } catch(err){
        res.status(500).json({error:'Error Finding Cards: '+err});
    }
});

module.exports = router;
