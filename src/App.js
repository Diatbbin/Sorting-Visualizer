import React, { useState } from 'react';
import axios from 'axios';

const SortingVisualizer = () => {
    const [data, setData] = useState();

    fetch('http://localhost:5000')
        .then(response => response.json())
        .then(data => {
        console.log('Backend response:', data);
        })
        .catch(error => {
        console.error('Error:', error);
        });

    return (
        <div>
            <ul>
                {data.map((item, index) => (
                    <li key={index}>{item}</li>
                ))}
            </ul>
        </div>
    );
}

export default SortingVisualizer;