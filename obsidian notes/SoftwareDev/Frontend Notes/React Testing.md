
## Testing with Jest
```javascript
import React from 'react';

const Button = ({ onClick, label }) => {
  return (
    <button onClick={onClick}>
      {label}
    </button>
  );
};

export default Button;


import { render, screen, fireEvent } from '@testing-library/react';
import Button from './Button';

// Test the rendering of the button
test('renders Button with label', () => {
  render(<Button label="Click Me" />);
  
  // Assert that the button is rendered with correct text
  const buttonElement = screen.getByText(/Click Me/i);
  expect(buttonElement).toBeInTheDocument();
});

// Test the button click event
test('calls onClick when clicked', () => {
  const handleClick = jest.fn();  // Mock function

  render(<Button onClick={handleClick} label="Click Me" />);
  
  const buttonElement = screen.getByText(/Click Me/i);
  
  // Simulate a click event
  fireEvent.click(buttonElement);
  
  // Assert that the mock function was called once
  expect(handleClick).toHaveBeenCalledTimes(1);
});

```

### Testing with props
```javascript
import React, { useState } from 'react';

const Counter = () => {
  const [count, setCount] = useState(0);

  return (
    <div>
      <p data-testid="count-value">Count: {count}</p>
      <button onClick={() => setCount(count + 1)}>Increment</button>
    </div>
  );
};

export default Counter;


import { render, screen, fireEvent } from '@testing-library/react';
import Counter from './Counter';

test('renders Counter with initial count', () => {
  render(<Counter />);
  const countElement = screen.getByTestId('count-value');
  expect(countElement).toHaveTextContent('Count: 0');
});

test('increments count when button is clicked', () => {
  render(<Counter />);
  
  const countElement = screen.getByTestId('count-value');
  const buttonElement = screen.getByText(/Increment/i);
  
  // Click the increment button
  fireEvent.click(buttonElement);
  
  // Assert that the count value has incremented
  expect(countElement).toHaveTextContent('Count: 1');
});

```


### Mocking api calls and functions

```javascript
import React, { useEffect, useState } from 'react';

const FetchData = ({ fetchData }) => {
  const [data, setData] = useState(null);

  useEffect(() => {
    fetchData().then(response => {
      setData(response);
    });
  }, [fetchData]);

  return (
    <div>
      {data ? <p data-testid="data">{data}</p> : <p>Loading...</p>}
    </div>
  );
};

export default FetchData;


import { render, screen } from '@testing-library/react';
import FetchData from './FetchData';

test('displays fetched data when fetchData resolves', async () => {
  // Mock the fetchData function
  const mockFetchData = jest.fn().mockResolvedValue('Fetched Data');

  render(<FetchData fetchData={mockFetchData} />);

  // Initially shows loading
  expect(screen.getByText(/Loading/i)).toBeInTheDocument();

  // Wait for the data to be loaded and displayed
  const dataElement = await screen.findByTestId('data');
  expect(dataElement).toHaveTextContent('Fetched Data');
  
  // Verify that the mock function was called
  expect(mockFetchData).toHaveBeenCalledTimes(1);
});

test('handles API failure', async () => {
  // Mock the fetchData function to reject
  const mockFetchData = jest.fn().mockRejectedValue('Error fetching data');

  render(<FetchData fetchData={mockFetchData} />);

  // Initially shows loading
  expect(screen.getByText(/Loading/i)).toBeInTheDocument();

  // Optionally, you can assert what happens if the data fails to load
  // For example, checking an error message or handling fallback logic.
});

```

### Testing with user interactions

```javascript

import { render, screen, userEvent } from '@testing-library/react';
import MyForm from './MyForm';

test('submitting the form displays a success message', async () => {
  render(<MyForm />);
  
  userEvent.type(screen.getByLabelText(/username/i), 'testuser');
  userEvent.click(screen.getByText(/submit/i));

  expect(await screen.findByText(/form submitted successfully/i)).toBeInTheDocument();
});

```