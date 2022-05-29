import math
import plotly.graph_objects as go

Points = []
Values = []

file = open("output.txt",'r')
for line in file:
    try:
        # l is a variable containing the entire line
        # Values in a document are formatted like this:
        # Point: Value\n
        # Following lines are used to take the formated input and convert it to usable data
        l = file.readline()
        l = l.split(':')
        l[1] = l[1][1:-1]
        Points.append(float(l[0]))
        Values.append(float(l[1]))

    except IndexError:
        pass
file.close()


# Figure definition and generation
fig = go.Figure(
    data=[go.Scatter(x=Points, y=Values,name="wynik")],
    layout=go.Layout(
        xaxis=dict(range=[0, 20], autorange=True),
        yaxis=dict(range=[-1.2, 1.2], autorange=True),
        title="Simple Spline 1/1+x^2",
        updatemenus=[dict(
            type='buttons',
            buttons=[dict(label='Play',
                          method='animate',
                          args=[None, {"frame": {"duration": 120, "redraw": True}, "fromcurrent": True,
                                       "transition": {"duration": 15}}]),
                     {"args": [[None], {"frame": {"duration": 0, "redraw": True},
                                        "mode": "immediate",
                                        "transition": {"duration": 0}}],
                      "label": "Pause",
                      "method": "animate"}
                     ])]))
fig.write_html("plot.html",auto_open=False)